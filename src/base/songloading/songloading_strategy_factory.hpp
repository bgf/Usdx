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

#ifndef SONGLOADING_STRATEGY_FACTORY_HPP
#define SONGLOADING_STRATEGY_FACTORY_HPP

#include "songloading_strategy_base_factory.hpp"

namespace usdx
{
	template <typename T>
	class SongloadingStrategyFactory : public SongloadingStrategyBaseFactory
	{
	private:
		T *songloader;

	public:
		SongloadingStrategyFactory(void) :
			SongloadingStrategyBaseFactory(T::get_fileextension()),
			songloader(NULL)
		{
		}

		virtual ~SongloadingStrategyFactory(void)
		{
			if (songloader) {
				delete songloader;
				songloader = NULL;
			}
		}

		T *get_songloader(void)
		{
			if (!songloader) {
				songloader = new T();
			}

			return songloader;
		}
	};
};

#endif