/*
 * UltraStar Deluxe - Karaoke Game
 *
 * UltraStar Deluxe is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 */

#if 0

#include "display.hpp"
#include <math.h>
#include <SDL/SDL.h>
#include <GL/glu.h>

// constants for software cursor effects time in milliseconds
const int Cursor_FadeIn_Time = 500;      // seconds the fade in effect lasts
const int Cursor_FadeOut_Time = 2000;    // seconds the fade out effect lasts
const int Cursor_AutoHide_Time = 5000;   // seconds until auto fade out starts if there is no mouse movement

namespace usdx
{
	Display* Display::get_instance(void)
	{
		if (!instance) {
			instance = new Display();
		}

		return instance;
	}

	Display::Display(void)
	{
		//popup hack
		check_ok = false;
		next_screen = NULL;
		next_screen_with_check = NULL;
		black_screen = false;

		// fade mod
		fade_state = 0;
		fade_enabled = (Ini.ScreenFade == 1);
		fade_failed = false;

		glGenTextures(2, fade_tex);

		for (int i = 0; i < 2; i++) {
			glBindTexture(GL_TEXTURE_2D, fade_tex[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		//Set LastError for OSD to No Error
		osd_last_error = "No Errors";

		// software cursor default values
		cursor_last_move = 0;
		cursor_visible = false;
		cursor_pressed = false;
		cursor_x = -1;
		cursor_y = -1;
		cursor_fade = false;
		cursor_hidden_by_screen = true;
	}

	Display::~Display(void)
	{
		glDeleteTextures(2, fade_tex);
	}

	bool Display::draw(void)
	{
		//We don't need this here anymore,
		//Because the background care about cleaning the buffers
		//glClearColor(1, 1, 1 , 0);
		//glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

		for (int s = 0; s < screens; s++)
		{
			int ScreenAct = s;

			//if Screens = 1 then ScreenX := 0;
			//if (Screens = 2) and (S = 1) then ScreenX := -1;
			//if (Screens = 2) and (S = 2) then ScreenX := 1;
			int ScreenX = 0;

			glViewPort((s-1) * screen_w / screens, 0, screen_w / screens, screen_h);

			// popup hack
			// check was successful... move on
			if (check_ok) {
				if (next_screen_with_check) {
					next_screen = next_screen_with_check;
					next_screen_with_check = NULL;
					check_ok = false;
				}
				else {
					// on end of game fade to black before exit
					black_screen = true;
				}
			}

			if (!next_screen && !black_screen) {
				current_screen->Draw();

				//popup mod
				if (screen_popup_error && screen_popup_error->visible)
					screen_popup_error->Draw();
				else if (screen_popup_info && screen_popup_info->visible)
					screen_popup_info->Draw();
				else if (screen_popup_check && screen_popup_check->visible)
					screen_popup_check->Draw();

				// fade mod
				fade_state = 0;
				if ((Ini.ScreenFade == 1) && !fade_failed)
					fade_enabled = true;
				else if (Ini.ScreenFade == 0)
					fade_enabled = false;
			}
			else {
				// disable fading if initialization failed
				if (fade_enabled && fade_failed)
					fade_enabled = false;

				if (fade_enabled && !fade_failed) {
					//Create Fading texture if we're just starting
					if (fade_state == 0) {
						// save old viewport and resize to fit texture
						glPushAttrib(GL_VIEWPORT_BIT);
						glViewPort(0, 0, 512, 512);

						// draw screen that will be faded
						current_screen->Draw();

						// clear OpenGL errors, otherwise fading might be disabled due to some
						// older errors in previous OpenGL calls.
						glGetError();

						// copy screen to texture
						glBindTexture(GL_TEXTURE_2D, fade_tex[s]);
						glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 512, 512, 0);

						GLenum glError = glGetError();
						if (glError != GL_NO_ERROR) {
							fade_failed = true;
							Log->LogWarn(std::string("Fading disabled: ") + gluErrorString(glError), "TDisplay.Draw");
						}

						// restore viewport
						glPopAttrib();

						// blackscreen-hack
						if (!black_screen)
							next_screen->on_show();

						// update fade state
						last_fade_time = SDL_GetTicks();
						if ((s == 1) || (screens == 1))
							fade_state++;
					} // end texture creation in first fading step

					//do some time-based fading
					unsigned int current_time = SDL_GetTicks();
					if ((current_time > last_fade_time + 30) && (s == 0))
					{
						fade_state += 4;
						last_fade_time = current_time;
					}

					// blackscreen-hack
					if (!black_screen)
						next_screen->Draw(); // draw next screen
					else if (screen_act == 0)
					{
						glClearColor(0, 0, 0 , 0);
						glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
					}

					// and draw old screen over it... slowly fading out
					float fade_state_square = (fade_state * fade_state) / 10000.0;

					glBindTexture(GL_TEXTURE_2D, fade_tex[s]);
					glColor4f(1, 1, 1, 1 - fade_state_square);

					glEnable(GL_TEXTURE_2D);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glEnable(GL_BLEND);
					glBegin(GL_QUADS);
					 glTexCoord2f(0 + fade_state_square, 0 + fade_state_square); glVertex2f(0,   600);
					 glTexCoord2f(0 + fade_state_square, 1 - fade_state_square); glVertex2f(0,   0);
					 glTexCoord2f(1 - fade_state_square, 1 - fade_state_square); glVertex2f(800, 0);
					 glTexCoord2f(1 - fade_state_square, 0 + fade_state_square); glVertex2f(800, 600);
					glEnd();
					glDisable(GL_BLEND);
					glDisable(GL_TEXTURE_2D);
				}

				// blackscreen hack
				else if (!black_screen)
					next_screen->on_show();

				if ((((fade_state > 40) || !fade_enabled) || fade_failed) && (s == 0)) {
					// fade out complete...
					fade_state = 0;
					current_screen->on_hide();
					current_screen->show_finish = false;
					current_screen = next_screen;
					next_screen = NULL;

					if (!black_screen) {
						current_screen->on_show_finish();
						current_screen->show_finish = true;
					}
					else {
						return false;
					}
				}
			}

			// Draw OSD only on first Screen if Debug Mode is enabled
			if (((Ini->Debug == 1) || (Params->Debug)) && (s == 0))
				draw_debug_information();

		} // for

		if (!black_screen)
			draw_cursor();

		return true;
	}

	// sets SDL_ShowCursor depending on options set in Ini
	void Display::set_cursor(void)
	{
		int cursor = 0;

		if ((current_screen != screen_sing) || (cursor_hidden_by_screen)) {

			// hide cursor on singscreen
			if ((Ini->Mouse == 0) and (Ini->FullScreen == 0))
				// show sdl (os) cursor in window mode even when mouse support is off
				cursor = 1;

			else if ((Ini->Mouse == 1))
				// show sdl (os) cursor when hardware cursor is selected
				cursor = 1;

			if ((Ini->Mouse != 2))
				cursor_hidden_by_screen = false;
		}
		else if ((Ini.Mouse != 2))
			cursor_hidden_by_screen = true;

		SDL_ShowCursor(cursor);

		if (Ini->Mouse == 2)
		{
			if (cursor_hidden_by_screen)
			{
				// show software cursor
				cursor_hidden_by_screen = false;
				cursor_visible = false;
				cursor_fade = false;
			}
			else if (current_screen == screen_sing)
			{
				// hide software cursor in singscreen
				cursor_hidden_by_screen = true;
				cursor_visible = false;
				cursor_fade = false;
			}
		}
	}

	// called by MoveCursor and OnMouseButton to update last move and start fade in
	void Display::update_cursor_fade(void)
	{
		unsigned int ticks = SDL_GetTicks();

		// fade in on movement (or button press) if not first movement
		if ((!cursor_visible) && (cursor_last_move != 0))
		{
			if (cursor_fade)  // we use a trick here to consider progress of fade out
				cursor_last_move = ticks - (int)(Cursor_FadeIn_Time * (1 - (ticks - cursor_last_move) / (float)Cursor_FadeOut_Time) + 0.5);
			else
				cursor_last_move = ticks;

			cursor_visible = true;
			cursor_fade = true;
		}
		else if (!cursor_fade)
		{
			cursor_last_move = ticks;
		}
	}

	// called when cursor moves, positioning of software cursor
	void Display::move_cursor(double x, double y)
	{
		if ((Ini->Mouse == 2) && ((x != cursor_x) || (y != cursor_y)))
		{
			cursor_x = x;
			cursor_y = y;

			update_cursor_fade();
		}
	}

	// called when left or right mousebutton is pressed or released
	void Display::on_mouse_button(bool pressed)
	{
		if (Ini->Mouse == 2)
		{
			cursor_pressed = pressed;
			update_cursor_fade();
		}
	}

	// draws software cursor
	void Display::draw_cursor(void)
	{
		float alpha;
		unsigned int ticks;
		if (Ini->Mouse == 2)
		{
			// draw software cursor
			ticks = SDL_GetTicks();

			if ((cursor_visible) && (cursor_last_move + Cursor_AutoHide_Time <= ticks))
			{
				// start fade out after 5 secs w/o activity
				cursor_visible = false;
				cursor_last_move = ticks;
				cursor_fade = true;
			}

			// fading
			if (cursor_fade)
			{
				if (cursor_visible)
				{
					// fade in
					if (cursor_last_move + Cursor_FadeIn_Time <= ticks)
						cursor_fade = false;
					else
						alpha = sin((ticks - cursor_last_move) * 0.5 * M_PI / Cursor_FadeIn_Time) * 0.7;
				}
				else
				{
					//fade out
					if (cursor_last_move + Cursor_FadeOut_Time <= ticks)
						cursor_fade = false;
					else
						alpha = cos((ticks - cursor_last_move) * 0.5 * M_PI / Cursor_FadeOut_Time) * 0.7;
				}
			}

			// no else if here because we may turn off fade in if block
			if (!cursor_fade)
			{
				if (cursor_visible)
					// alpha when cursor visible and not fading
					alpha = 0.7;
				else
					// alpha when cursor is hidden
					alpha = 0;
			}

			if ((alpha > 0) && (!cursor_hidden_by_screen))
			{
				glColor4f(1, 1, 1, alpha);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);

				if ((cursor_pressed) && (tex_cursor_pressed->tex_num > 0))
					glBindTexture(GL_TEXTURE_2D, tex_cursor_pressed->tex_num);
				else
					glBindTexture(GL_TEXTURE_2D, tex_cursor_unpressed->tex_num);

				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(cursor_x, cursor_x);

				glTexCoord2f(0, 1);
				glVertex2f(cursor_x, cursor_y + 32);

				glTexCoord2f(1, 1);
				glVertex2f(cursor_x + 32, cursor_y + 32);

				glTexCoord2f(1, 0);
				glVertex2f(cursor_x + 32, cursor_y);
				glEnd();

				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}

	bool Display::parse_input(unsigned int pressed_key, UCS4Char char_code, bool pressed_down)
	{
		if (next_screen)
			return next_screen->parse_input(pressed_key, char_code, pressed_down);

		if (current_screen)
			return current_screen->parse_input(pressed_key, char_code, pressed_down);

		return true;
	}

	void Display::save_screen_shot()
	{
		Path *file_name;
		std::string prefix;
		char *screen_data;
		SDL_Surface *surface;
		bool success;
		int align;
		int row_size;

		// Exit if Screenshot-path does not exist or read-only
		if (!screenshots_path)
			return;

		for (int num = 1; num < 10000; num++)
		{
			/** TODO:

			// fill prefix to 4 digits with leading '0', e.g. '0001'
			Prefix = Format('screenshot%.4d', [Num]);
			FileName = ScreenshotsPath.Append(Prefix + '.png');

			if not FileName.Exists()
				       break;
			*/
		}

		// we must take the row-alignment (4byte by default) into account
		glGetIntegerv(GL_PACK_ALIGNMENT, &align);

		// calc aligned row-size
		row_size = ((screen_w * 3 + (align - 1)) / align) * align;

		malloc(screen_data, row_size * screen_h);
		glReadPixels(0, 0, screen_w, screen_h, GL_RGB, GL_UNSIGNED_BYTE, screen_data);

		// on big endian machines (powerpc) this may need to be changed to
		// Needs to be tests. KaMiSchi Sept 2008
		// in this case one may have to add " glext, " to the list of used units
		//  glReadPixels(0, 0, ScreenW, ScreenH, GL_BGR, GL_UNSIGNED_BYTE, ScreenData);
		Surface = SDL_CreateRGBSurfaceFrom(
			screen_data, screen_w, screen_h, 24, row_size,
			0x0000ff, 0x00ff00, 0xff0000, 0);

		//  Success = WriteJPGImage(FileName, Surface, 95);
		//  Success = WriteBMPImage(FileName, Surface);
		success = WritePNGImage(file_name, surface);
		if (success)
			ScreenPopupInfo->ShowPopup(Format(Language.Translate("SCREENSHOT_SAVED"), [FileName.GetName.ToUTF8()]));
		else
			ScreenPopupError->ShowPopup(Language.Translate("SCREENSHOT_FAILED"));

		SDL_FreeSurface(surface);
		free(screen_data);
	}

	//------------
	// DrawDebugInformation - procedure draw fps and some other informations on screen
	//------------
	void Display::draw_debug_information()
	{
		// Some White Background for information
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 0.5);
		glBegin(GL_QUADS);
		 glVertex2f(690, 44);
		 glVertex2f(690, 0);
		 glVertex2f(800, 0);
		 glVertex2f(800, 44);
		glEnd();
		glDisable(GL_BLEND);

		// set font specs
		SetFontStyle(0);
		SetFontSize(21);
		SetFontItalic(false);
		glColor4f(0, 0, 0, 1);

		// calculate fps
		unsigned int ticks = SDL_GetTicks();
		if (ticks >= next_fps_swap) {
			last_fps = fps_counter * 4;
			fps_counter = 0;
			next_fps_swap = ticks + 250;
		}

		fps_counter++;

		// draw text

		// TODO:
		// fps
		SetFontPos(695, 0);
		glPrint ("FPS: " + itoa(last_fps));

		// rspeed
		SetFontPos(695, 13);
		glPrint ("RSpeed: " + itoa((int)(1000 * time_mid)));

		// lasterror
		SetFontPos(695, 26);
		glColor4f(1, 0, 0, 1);
		glPrint(osd_last_error.c_str());

		glColor4f(1, 1, 1, 1);
	}
};

#endif
