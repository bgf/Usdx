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

#ifndef STATS_DATABASE_HPP
#define STATS_DATABASE_HPP

#include <ctime>
#include <string>
#include <log4cxx/logger.h>
#include "database.hpp"

namespace usdx
{
	/**
	 * Wrapper for statistic database.
	 */
	class StatDatabase : public Database
	{
	private:
		static log4cxx::LoggerPtr log;

	public:
		StatDatabase(std::string filename);
		~StatDatabase(void);

		/**
		 * Convert a timestamp to a data representation in a string.
		 *
		 * @param time Pointer to a char buffer that will contain the
		 * 	the date string.
		 * @param max Maximum bytes that could be written to the buffer.
		 * @param timestamp Timestamp to convert to the string.
		 * @return Pointer to the buffer supplied as first parameter,
		 * 	containing:
		 *		- only a '\\0' at first position if timestamp was
		 * 		  0 or if max was to short to contain the date
		 *		- the date string with the terminating '\\0'
		 */
		static char* format_date(char* time, size_t max, time_t timestamp);

		static const std::wstring usdx_scores;
		static const std::wstring usdx_songs;
		static const std::wstring usdx_statistics_info;


#ifdef STAT_DATABASE_TEST
		// for testing private members
		friend class StatDatabaseTest;
#endif
	};
};

#endif
