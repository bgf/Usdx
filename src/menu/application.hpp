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

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>
#include <log4cxx/logger.h>
#include <list>

#include "drawable_control.hpp"
#include "frame.hpp"

namespace usdx
{
	class Application : public DrawableControl
	{
	private:
		static log4cxx::LoggerPtr log;
		static Application* instance;

		SDL_Surface* display;
		Frame* frame;
		FPSmanager* fps_manager;

		bool running;

		int display_width;
		int display_height;

		int frames_per_second;

		std::list<DrawableControl*> overlays;

		/**
		 * This is the main loop.
		 */
		void main_loop(SDL_Surface* display);

		void init_fps_manager(void);

	protected:
		Application(Control* parent);

		void draw(SDL_Surface* display) const;

	public:
		virtual ~Application();

		static Application* get_instance(void);

		void run(void);

		const Frame* get_current_frame(void) const;
		void set_current_frame(Frame* new_frame);

		const int get_display_width(void) const;
		const int get_display_height(void) const;

		const int get_frames_per_second(void) const;
		void set_frames_per_second(int fps);

		void repaint(SDL_Surface* display) const;
	};
};

#endif
