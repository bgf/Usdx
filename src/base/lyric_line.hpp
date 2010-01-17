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

#ifndef LYRIC_LINE_HPP
#define LYRIC_LINE_HPP

#include <list>
#include "lyric_word.hpp"

namespace usdx
{
	class LyricLine
	{
	private:
		std::list<LyricWord*> words;
		int start; ///< in beats
		int end; ///< in beats
	public:
		LyricLine(int start = 0);
		virtual ~LyricLine();

		void set_end(int end);
		const int get_end(void) const;

		void set_start(int start);
		const int get_start(void) const;

		void add_word(LyricWord* word);
	};
};

#endif
