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

#ifndef SOFTWARE_MOUSE_POINTER_HPP
#define SOFTWARE_MOUSE_POINTER_HPP

#include "drawable_control.hpp"
#include "control.hpp"
#include "event_manager.hpp"
#include "texture.hpp"

#include <boost/signals2.hpp>
#include <boost/thread/mutex.hpp>
#include <GL/gl.h>

namespace usdx
{
	class SoftwareMousePointer : public DrawableControl
	{
	private:
		int x;
		int y;

		GLfloat vertices[12];
		GLubyte color[16];
		GLfloat texture[8];

		Texture* texture_normal;
		Texture* texture_pressed;

		boost::signals2::connection mouse_move_connection;

		boost::mutex mutex;

	protected:
		void draw(void);

	public:
		SoftwareMousePointer(Control* parent, EventManager* event_manager);
		virtual ~SoftwareMousePointer();

		void on_mouse_move(int x, int y);
	};
};


#endif
