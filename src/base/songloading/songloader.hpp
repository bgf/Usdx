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

#ifndef SONGLOADER_HPP
#define SONGLOADER_HPP

#include <map>
#include <log4cxx/logger.h>
#include "songloading_strategy.hpp"
#include "song.hpp"
#include "utils/base_exception.hpp"

namespace usdx
{
	class NoStrategyException : public BaseException
	{
	public:
		NoStrategyException(const std::string& message) : BaseException(message) {};
		~NoStrategyException () throw () {};
	};

	class Songloader
	{
	private:
		static log4cxx::LoggerPtr log;

		Songloader(void);

		std::map<std::string, SongloadingStrategy*> strategies;

		/**
		 * Singleton
		 */
		static Songloader *instance;

	public:
		static Songloader *get_instance(void);

		virtual ~Songloader(void);

		Song* load_header(std::string filename);
		Song* load_song(Song* song);
	};
};

#endif
