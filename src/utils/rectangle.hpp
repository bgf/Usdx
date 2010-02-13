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

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "utils/point.hpp"
#include "utils/dimension.hpp"

namespace usdx
{
	class Rectangle
	{
	private:
		Point point1;
		Point point2;
	public:
		Rectangle(float x1, float y1, float x2, float y2);
		Rectangle(const Point& point1, const Point& point2);
		Rectangle(const Point& point1, float width, float height);
		Rectangle(const Point& point1, const Dimension& dimension);
		Rectangle(const Rectangle& rectangle);

		const Point& get_point1(void) const;
		const Point& get_point2(void) const;
		const float get_width(void) const;
		const float get_height(void) const;
	};
};

#endif
