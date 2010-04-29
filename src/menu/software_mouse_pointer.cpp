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
#include <SDL/SDL.h>

namespace usdx
{
	SoftwareMousePointer::SoftwareMousePointer(Control* parent, EventManager* event_manager)
		: DrawableControl(parent), x(-1), y(-1)
	{
		texture = new Image(L"game/themes/Deluxe/interface/cursor.png");

		mouse_move_connection = event_manager->mouse_move.connect(
			boost::bind(&SoftwareMousePointer::on_mouse_move, this, _1, _2));
	}

	SoftwareMousePointer::~SoftwareMousePointer()
	{
		mouse_move_connection.disconnect();

		if (texture != NULL) {
			delete texture;
			texture = NULL;
		}
	}

	void SoftwareMousePointer::draw(SDL_Surface* display) const
	{
		if (x >= 0 && y >= 0) {
			SDL_Rect rcDest = { x, y, 0, 0 };
			SDL_BlitSurface((SDL_Surface*)texture->get_surface(), NULL, display, &rcDest);
		}
	}

	void SoftwareMousePointer::on_mouse_move(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

