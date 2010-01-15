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

#include <string>
#include <algorithm>
#include "songloading_strategy_txt.hpp"
#include "utils/file.hpp"

namespace usdx
{
	log4cxx::LoggerPtr SongloadingStrategyTxt::log =
		log4cxx::Logger::getLogger(
			"usdx.base.songloading.SongloadingStrategyTxt");

	SongloadingStrategyTxt::SongloadingStrategyTxt(void)
	{
	}

	SongloadingStrategyTxt::~SongloadingStrategyTxt(void)
	{
	}

	std::pair<std::string, std::string> SongloadingStrategyTxt::split_header_field(std::string &line)
	{
		std::size_t pos = line.find(':');

		if (line[0] != '#' || pos == std::string::npos) {
			LOG4CXX_DEBUG(log, "Tried to parse invalid header line: '" << line << "'");
			throw "Invalid header!";
		}

		std::pair<std::string, std::string> result;

		// copy the substring until ':', without # to result.first and
		// transform to upper case
		result.first.resize(pos - 1);
		std::transform(line.begin() + 1, line.begin() + pos,
			       result.first.begin(), toupper);

		// line is already ltrimmed
		rtrim(result.first);

		result.second = line.substr(pos + 1);

		// line is already rtrimmed
		ltrim(result.second);

		LOG4CXX_DEBUG(log, "Found header: '" << result.first << "' with value '" << result.second << "'");

		return result;
	}

	std::string& SongloadingStrategyTxt::ltrim(std::string& line)
	{
		std::size_t found = line.find_first_not_of(" \t\n\r");
		if (found != std::string::npos && found >= 1) {
			line.erase(0, found - 1);
		}

		return line;
	}

	std::string& SongloadingStrategyTxt::rtrim(std::string& line)
	{
		std::size_t found = line.find_last_not_of(" \t\n\r");
		if (found != std::string::npos) {
			line.erase(found + 1);
		}

		return line;
	}

	std::string& SongloadingStrategyTxt::trim(std::string& line)
	{
		return ltrim(rtrim(line));
	}

	Song* SongloadingStrategyTxt::load_song(Song *song)
	{
		File file(song->get_filename());
		std::string line;

		while (file.stream().good()) {
			file.stream() >> line;

			// do not remove spaces at line ending, that are maybe
			// spaces in lyrics
			ltrim(line);

			if (line[0] == '#') {
				// ignore, header already read
			}
			else if (line[0] == 'E') {
				// song end
				break;
			}
			else if (line[0] == '-') {
				// line break
			}
			else if (line[0] == 'B') {
				// new bpm
			}
			else {
				// normal line
			}
		}

		// fill song

		return song;
	}

	Song* SongloadingStrategyTxt::load_header(const std::string& filename)
	{
		File file(filename);
		std::string line;
		std::map<std::string, std::string> header_fields;

		bool header = true, notes_found = false;
		while (file.stream().good()) {
			std::getline(file.stream(), line);

			trim(line);
			LOG4CXX_DEBUG(log, "Line: " << line);

			if (header && line[0] == '#') {

				// header
				header_fields.insert(split_header_field(line));
			}
			else {
				if (header) {
					// end of header
					header = false;
				}

				if (line[0] == ':' || line[0] == '*' || line[0] == 'F') {
					notes_found = true;
					break;
				}
			}
		}

		if (! notes_found) {
			LOG4CXX_WARN(log, "Song: '" << filename  << "' has no notes. Ignoring!");
			throw "No notes.";
		}

		// fill song
		return new Song(filename, header_fields);
	}
};
