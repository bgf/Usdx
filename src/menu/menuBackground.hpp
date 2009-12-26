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

#ifndef MENUBACKGROUND_HPP
#define MENUBACKGROUND_HPP

namespace usdx
{
	// Exception
	class MenuBackgroundException { };

	// MenuBackground - abstract class for MenuBackgrounds
	class MenuBackground
	{
	public:
		virtual void draw(void) = 0;

		// optional methods
		virtual ~MenuBackground() {}

		virtual void on_show(void) {}
		virtual void on_finish(void) {}

	protected:
		// no copy and no assignment
		MenuBackground(const MenuBackground&);
		MenuBackground& operator=(const MenuBackground&);
	};

	class MenuBackgroundNone : MenuBackground
	{
		virtual void draw(void);
	};
};

#endif
