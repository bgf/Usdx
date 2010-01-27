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

#include <algorithm>
#include <exception>
#include <sstream>
#include <string>

#include "songloading_strategy_txt.hpp"
#include "utils/file.hpp"
#include "utils/locale_independent_float.hpp"

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

	std::string& SongloadingStrategyTxt::ltrim_newlines(std::string& line)
	{
		std::size_t found = line.find_first_not_of("\n\r");
		if (found != std::string::npos) {
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

	std::string& SongloadingStrategyTxt::rtrim_newlines(std::string& line)
	{
		std::size_t found = line.find_last_not_of("\n\r");
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
		LOG4CXX_DEBUG(log, "Starting loading song from file: " << song->get_filename());

		File file(song->get_filename());

		int line_number = 0;
		while (file.stream().good() && parse_line(song, file, ++line_number));

		// fill song

		return song;
	}

	bool SongloadingStrategyTxt::parse_line(Song* song, File& file, const int line_number)
	{
		std::string line;
		std::getline(file.stream(), line);

		char type;
		std::istringstream linestream(line);
		linestream >> std::skipws >> type;

		if (type == '#') {
			// ignore, header already read
		}
		else if (type == 'E') {
			// song end
			if (file.stream().eof()) {
				LOG4CXX_WARN(log, "End marker found in line " << line_number <<
					     " before end of file: '" << song->get_filename() << "'.");
			}

			return false;
		}
		else if (type == '-') {
			parse_newline(song, linestream, line_number);
		}
		else if (type == 'B') {
			parse_bpm(song, linestream, line_number);
		}
		else if (type == ':' || type == 'F' || type == '*') {
			parse_note(song, type, linestream, line_number);
		}
		else {
			LOG4CXX_WARN(log, "Unknown line in song: '" << line <<
				     "' in file: " << song->get_filename() <<
				     " at line " << line_number);
		}

		return true;
	}

	void SongloadingStrategyTxt::parse_newline(Song *song, std::istringstream& linestream, const int line_number)
	{
		// line break
		int line_out, line_in = -1;

		linestream >> line_out;
		if (linestream.good()) {
			linestream >> line_in;
			LOG4CXX_DEBUG(log, "Found newline in line " <<
				      line_number << " with out of last line with "
				      << line_out << " and in of next line " << line_in);
		}
		else {
			LOG4CXX_DEBUG(log, "Found newline in line " <<
				      line_number << " with out of last line with "
				      << line_out);
		}

		song->new_line(line_out, line_in);
	}

	void SongloadingStrategyTxt::parse_bpm(Song *song, std::istringstream& linestream, const int line_number)
	{
		// new bpm
		int beat;
		LocaleIndependentFloat new_bpm;

		linestream >> beat >> new_bpm;
		LOG4CXX_DEBUG(log, "Found new bpm in line " <<
			      line_number << " starting at beat: " <<
			      beat << " and new bpm of " << new_bpm.get_value());
		song->new_bpm(beat, new_bpm.get_value());
	}

	void SongloadingStrategyTxt::parse_note(Song *song, char type, std::istringstream& linestream, const int line_number)
	{
		// normal line
		int beat, length, height;
		std::string lyric;

		linestream >> beat >> length >> height >> std::noskipws;
		linestream.ignore();
		getline(linestream, lyric);
		rtrim_newlines(lyric);

		LOG4CXX_DEBUG(log, "Found lyric: '" << lyric << "' at line: " << line_number <<
			      " at beat: " << beat << " with length: " << length <<
			      " at height: " << height);
		song->new_note(type, beat, length, height, lyric);
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
