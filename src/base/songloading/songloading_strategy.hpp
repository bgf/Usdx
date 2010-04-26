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

#ifndef SONGLOADING_STRATEGY_HPP
#define SONGLOADING_STRATEGY_HPP

#include <string>
#include <boost/filesystem.hpp>
#include "song.hpp"

#define _USDX_JOIN(strategy, line) _USDX_JOIN1(strategy, line)
#define _USDX_JOIN1(strategy, line) autoregistration__strategy__##line

/* Macros to simplify registration of SongLoadingStrategy */
#define REGISTER_SONGLOADING_STRATEGY(strategy) \
	static SongloadingStrategyFactory<strategy> \
	_USDX_JOIN(strategy, __LINE__)


namespace usdx
{
	class SongloadingStrategy
	{
	protected:
		SongloadingStrategy() {};

	public:
		virtual ~SongloadingStrategy() {};

		virtual Song* load_song(Song* song) = 0;
		virtual Song* load_header(const boost::filesystem::wpath& filename) = 0;
	};
};

#endif