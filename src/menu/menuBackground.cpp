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

#include "menuBackground.hpp"
#include <GL/gl.h>

int screen_act = 1;

namespace usdx
{
	void MenuBackgroundNone::draw(void)
	{
		// clear just once when in dual screen mode
		if (screen_act == 0)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	MenuBackgroundColor::MenuBackgrundColor(RGB &color)
	{
		this->color = color;
	}

	void MenuBackgroundColor::draw(void)
	{
		// just clear once, even when using two screens
		if (screen_act == 1) {
			glClearColor(color.r, color.g, color.b, 0);
			glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
		}
	}
};
