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

#include "software_mouse_pointer.hpp"
#include <GL/gl.h>
#include <iostream>

namespace usdx
{
	SoftwareMousePointer::SoftwareMousePointer(Control* parent, EventManager* event_manager)
		: DrawableControl(parent), x(-1), y(-1)
	{
		this->vertices[0] = 0.0f;
		this->vertices[1] = 40.0f;
		this->vertices[2] = 0.0f;
		this->vertices[3] = 40.0f;
		this->vertices[4] = 40.0f;
		this->vertices[5] = 0.0f;
		this->vertices[6] = 40.0f;
		this->vertices[7] = 0.0f;
		this->vertices[8] = 0.0f;
		this->vertices[9] = 0.0f;
		this->vertices[10] = 0.0f;
		this->vertices[11] = 0.0f;

		this->color[0] = 255;
		this->color[1] = 255;
		this->color[2] = 255;
		this->color[3] = 100;
		this->color[4] = 255;
		this->color[5] = 255;
		this->color[6] = 255;
		this->color[7] = 100;
		this->color[8] = 255;
		this->color[9] = 255;
		this->color[10] = 255;
		this->color[11] = 100;
		this->color[12] = 255;
		this->color[13] = 255;
		this->color[14] = 255;
		this->color[15] = 100;

		this->texture[0] = 0.0f;
		this->texture[1] = 1.0f;
		this->texture[2] = 1.0f;
		this->texture[3] = 1.0f;
		this->texture[4] = 1.0f;
		this->texture[5] = 0.0f;
		this->texture[6] = 0.0f;
		this->texture[7] = 0.0f;

		texture_normal = new Texture(L"game/themes/Deluxe/interface/cursor.png");
		texture_pressed = new Texture(L"game/themes/Deluxe/interface/cursor_pressed.png");

		mouse_move_connection = event_manager->mouse_move.connect(
			boost::bind(&SoftwareMousePointer::on_mouse_move, this, _1, _2));
	}

	SoftwareMousePointer::~SoftwareMousePointer()
	{
		mouse_move_connection.disconnect();

		if (texture_normal != NULL) {
			delete texture_normal;
			texture_normal = NULL;
		}
	}

	void SoftwareMousePointer::draw(void)
	{
		glLoadIdentity();

		boost::mutex::scoped_lock lock(mutex);

		if (x >= 0 && y >= 0) {
			glTranslatef(x, y, 0.0f);
			lock.unlock();

			glBindTexture(GL_TEXTURE_2D, texture_normal->get_texture());

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
			glTexCoordPointer(2, GL_FLOAT, 0, texture);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
		}
	}

	void SoftwareMousePointer::on_mouse_move(int x, int y)
	{
		boost::mutex::scoped_lock lock(mutex);

		this->x = x;
		this->y = y;
	}
};

