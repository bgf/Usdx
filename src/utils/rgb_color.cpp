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

#include "rgb_color.hpp"

namespace usdx
{
	RgbColor::RgbColor(int red, int green, int blue)
		: red(red / 255.0f), green(green / 255.0f), blue(blue / 255.0f)
	{
	}

	RgbColor::RgbColor(float red, float green, float blue)
		: red(red), green(green), blue(blue)
	{
	}

	float RgbColor::get_red(void) const
	{
		return red;
	}

	float RgbColor::get_green(void) const
	{
		return green;
	}

	float RgbColor::get_blue(void) const
	{
		return blue;
	}
};
