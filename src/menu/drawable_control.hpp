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

#ifndef DRAWABLE_CONTROL_HPP
#define DRAWABLE_CONTROL_HPP

#include <SDL/SDL.h>

#include "drawable.hpp"
#include "control.hpp"

namespace usdx
{
	class DrawableControl : public Drawable, public Control
	{
	protected:
                /**
		 * Pure virtual method, that descendant classes have to
		 * implement. (Should be left pure virtual.)
		 */
		virtual void draw(SDL_Surface* display) const = 0;

	public:
		DrawableControl(Control* parent);
		virtual ~DrawableControl();
	};
};

#endif