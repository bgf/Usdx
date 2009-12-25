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

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <GL/gl.h>
#include <string>

namespace usdx
{
	typedef unsigned long UCS4Char;

	class Display
	{
	protected:
		//fade-to-black-hack
		bool black_screen;

		bool fade_enabled; // true if fading is enabled
		bool fade_failed;
		int fade_state;  // fading state, 0 means that the fade texture must be initialized
		unsigned int last_fade_time; // last fade update time

		GLuint fade_tex[2];

		unsigned int fps_counter;
		unsigned int last_fps;
		unsigned int next_fps_swap;

		std::string osd_last_error;

		// software cursor data
		double cursor_x;
		double cursor_y;
		bool cursor_pressed;
		bool cursor_hidden_by_screen; // hides software cursor and deactivate auto fade in

		// used for cursor fade out when there is no movement
		bool cursor_visible;
		unsigned int cursor_last_move;
		bool cursor_fade;

		void draw_debug_information(void);

		// called by MoveCursor and OnMouseButton to update last move and start fade in
		void update_cursor_fade(void);

		// Singleton
		Display(void);

		static Display* instance;
	public:
		static Display* get_instance();

		Menu* next_screen;
		Menu* current_screen;

		//popup data
		Menu* next_screen_with_check;
		bool check_ok;

		// FIXME: Fade is set to 0 in UMain and other files but not used here anymore.
		float Fade;

		~Display(void);

		void save_screen_shot(void);

		bool draw(void);

		// calls ParseInput of cur or next Screen if assigned
		bool parse_input(unsigned int pressed_key, UCS4Char char_code, bool pressed_down);

		// sets SDL_ShowCursor depending on options set in Ini
		void set_cursor(void);

		// called when cursor moves, positioning of software cursor
		void move_cursor(double x, double y);

		// called when left or right mousebutton is pressed or released
		void on_mouse_button(bool pressed);

		// draws software cursor
		void draw_cursor();
	};
};

#endif
