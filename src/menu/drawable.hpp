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

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SDL/SDL.h>

namespace usdx
{
	/**
	 * Abstract base class for all classes that could be draw.
	 */
	class Drawable
	{
	private:
		bool visible;

	protected:
		/**
		 * Pure virtual method, that descendant classes have to implement.
		 */
		virtual void draw(SDL_Surface* display) const = 0;

	public:
 		Drawable(void);
		virtual ~Drawable(void) {};

		/**
		 * Method for redraw this Object. If visible issues draw.
		 */
		void repaint(SDL_Surface* display) const;

		/**
		 * Setter for visible.
		 */
		virtual void set_visible(bool value);

		/**
		 * Getter for visible.
		 */
		virtual const bool get_visible(void) const;
	};
};

#endif
