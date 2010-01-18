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

#ifndef SONGLOADING_STRATEGY_TXT_HPP
#define SONGLOADING_STRATEGY_TXT_HPP

#include <string>
#include <log4cxx/logger.h>
#include "songloading_strategy.hpp"
#include "utils/file.hpp"

namespace usdx
{
	class SongloadingStrategyTxt : public SongloadingStrategy
	{
	private:
		static log4cxx::LoggerPtr log;

		/**
		 * Split the header field in name and value.
		 */
		std::pair<std::string, std::string> split_header_field(std::string &line);

		/**
		 * Removes whitespaces in front of the string.
		 */
		std::string& ltrim(std::string& line);

		/**
		 * Removes whitespaces behind the string.
		 */
		std::string& rtrim(std::string& line);

		/**
		 * Removes whitespaces in front of the string and behind it.
		 */
		std::string& trim(std::string& line);

		bool parse_line(Song* song, File& file, const int line_number);
		void parse_newline(Song* song, std::istringstream& linestream, const int line_number);
		void parse_bpm(Song* song, std::istringstream& linestream, const int line_number);
		void parse_note(Song* song, char type, std::istringstream& linestream, const int line_number);


	public:
		SongloadingStrategyTxt();
		virtual ~SongloadingStrategyTxt();

		virtual Song* load_song(Song* song);
		virtual Song* load_header(const std::string& filename);
	};
};

#endif
