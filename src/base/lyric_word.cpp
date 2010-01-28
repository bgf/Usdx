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

#include "lyric_word.hpp"

namespace usdx
{
	LyricWord::LyricWord(const wchar_t type,
			     const int beat,
			     const int length,
			     const int height,
			     const std::wstring& lyric) :
		beat(beat), length(length), height(height), text(lyric)
	{
		if (type == L':') {
			this->type = nt_normal;
		}
		else if (type == L'*') {
			this->type = nt_golden;
		}
		else if (type == L'F') {
			this->type = nt_freestyle;
		}
	}

	LyricWord::~LyricWord(void)
	{
	}
};
