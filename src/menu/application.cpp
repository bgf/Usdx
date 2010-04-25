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

#include "application.hpp"
#include <exception>

namespace usdx
{
	log4cxx::LoggerPtr Application::log =
		log4cxx::Logger::getLogger("usdx.menu.application");

	Application* Application::instance = NULL;

	Application::Application(Control* parent)
		: DrawableControl(parent), display(NULL), frame(NULL),
		  running(false), display_width(800), display_height(600)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

		fps_manager = new FPSmanager();
	}

	Application::~Application()
	{
		if (fps_manager) {
			delete fps_manager;
			fps_manager = NULL;
		}

		SDL_Quit();
	}

	Application* Application::get_instance(void)
	{
		if (! instance) {
			instance = new Application(NULL);
		}

		return instance;
	}

	void Application::draw(SDL_Surface* screen) const
	{
		if (frame) {
			frame->repaint(screen);
		}
	}

	const Frame *Application::get_current_frame(void) const
	{
		return frame;
	}

	void Application::set_current_frame(Frame* new_frame)
	{
		frame = new_frame;
		repaint(display);
	}

	void Application::main_loop(SDL_Surface* display)
	{
		SDL_Event event;

		running = true;
		while (running) {
			// repaint everything
			repaint(display);
			SDL_Flip(display);

			LOG4CXX_ERROR(log, L"repaint");

			// poll current events
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					running = false;
					return;
				}
			}

			// limit frames
			SDL_framerateDelay(fps_manager);
		}
	}

	void Application::run(void)
	{
		if (! display) {
			display = SDL_SetVideoMode(display_width,
						   display_height,
						   24,
						   SDL_SWSURFACE |
						   SDL_DOUBLEBUF);
		}

		if (! display) {
			LOG4CXX_ERROR(log, L"SDL_SetVideoMode failed.");
			throw new std::exception();
		}

		SDL_initFramerate(fps_manager);
		SDL_setFramerate(fps_manager, 50);

		main_loop(display);
	}

	const int Application::get_display_width(void) const
	{
		return display_width;
	}

	const int Application::get_display_height(void) const
	{
		return display_height;
	}
};
