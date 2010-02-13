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

#include "rectangle.hpp"

namespace usdx
{
	Rectangle::Rectangle(float x1, float y1, float x2, float y2) :
		point1(x1, y1), point2(x2, y2)
	{
	}

	Rectangle::Rectangle(const Point& point1, const Point& point2) :
		point1(point1), point2(point2)
	{
	}

	Rectangle::Rectangle(const Point& point1, float width, float height) :
		point1(point1),
		point2(point1.get_x() + width, point1.get_y() + height)
	{
	}

	Rectangle::Rectangle(const Point& point1, const Dimension& dimension) :
		point1(point1),
		point2(point1.get_x() + dimension.get_width(),
		       point1.get_y() + dimension.get_height())
	{
	}

	Rectangle::Rectangle(const Rectangle& rectangle) :
		point1(rectangle.point1), point2(rectangle.point2)
	{
	}

	const Point& Rectangle::get_point1(void) const
	{
		return point1;
	}

	const Point& Rectangle::get_point2(void) const
	{
		return point2;
	}

	const float Rectangle::get_width(void) const
	{
		return point2.get_x() - point1.get_x();
	}

	const float Rectangle::get_height(void) const
	{
		return point2.get_y() - point1.get_y();
	}
};
