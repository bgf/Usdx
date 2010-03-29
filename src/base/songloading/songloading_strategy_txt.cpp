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

#include <boost/algorithm/string.hpp>

#include "songloading_strategy_txt.hpp"
#include "utils/unicode_file.hpp"
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

	std::pair<std::wstring, std::wstring> SongloadingStrategyTxt::split_header_field(std::wstring &line)
	{
		std::size_t pos = line.find(L':');

		if (line[0] != L'#' || pos == std::wstring::npos) {
			LOG4CXX_DEBUG(log, L"Tried to parse invalid header line: '" << line << L"'");
			throw "Invalid header!";
		}

		std::pair<std::wstring, std::wstring> result;

		// copy the substring until ':', without # to result.first and
		// transform to upper case
		result.first.resize(pos - 1);
		std::transform(line.begin() + 1, line.begin() + pos,
			       result.first.begin(), toupper);

		// line is already ltrimmed
		boost::trim_right(result.first);

		result.second = line.substr(pos + 1);

		// line is already rtrimmed
		boost::trim_left(result.second);

		LOG4CXX_DEBUG(log, L"Found header: '" << result.first << L"' with value '" << result.second << L"'");

		return result;
	}

	Song* SongloadingStrategyTxt::load_song(Song *song)
	{
		LOG4CXX_DEBUG(log, L"Starting loading song from file: " << song->get_filename());

		UnicodeFile file(song->get_filename());

		int line_number = 0;
		while (file.stream().good() && parse_line(song, file, ++line_number));

		// fill song

		return song;
	}

	bool SongloadingStrategyTxt::parse_line(Song* song, UnicodeFile& file, const int line_number)
	{
		try {
			std::wstring line;
			std::getline(file.stream(), line);

			wchar_t type;
			std::wistringstream linestream(line);
			linestream >> std::skipws >> type;

			if (type == L'#') {
				// ignore, header already read
			}
			else if (type == L'E') {
				// song end
				if (file.stream().eof()) {
					LOG4CXX_WARN(log, L"End marker found in line " << line_number <<
						     L" before end of file: '" << song->get_filename() << L"'.");
				}

				return false;
			}
			else if (type == L'-') {
				parse_newline(song, linestream, line_number);
			}
			else if (type == L'B') {
				parse_bpm(song, linestream, line_number);
			}
			else if (type == L':' || type == L'F' || type == L'*') {
				parse_note(song, type, linestream, line_number);
			}
			else {
				LOG4CXX_WARN(log, L"Unknown line in song: '" << line <<
					L"' in file: " << song->get_filename() <<
					     L" at line " << line_number);
			}
		}
		catch (std::exception &e) {
			LOG4CXX_WARN(log, L"Error in song file at line " <<
				     line_number << L": " << e.what());
		}

		return true;
	}

	void SongloadingStrategyTxt::parse_newline(Song *song, std::wistringstream& linestream, const int line_number)
	{
		// line break
		int line_out, line_in = -1;

		linestream >> line_out;
		if (linestream.good()) {
			linestream >> line_in;
			LOG4CXX_DEBUG(log, L"Found newline in line " <<
				      line_number << L" with out of last line with " <<
				      line_out << L" and in of next line " << line_in);
		}
		else {
			LOG4CXX_DEBUG(log, L"Found newline in line " <<
				      line_number << L" with out of last line with " <<
				      line_out);
		}

		song->new_line(line_out, line_in);
	}

	void SongloadingStrategyTxt::parse_bpm(Song *song, std::wistringstream& linestream, const int line_number)
	{
		// new bpm
		int beat;
		LocaleIndependentFloat new_bpm;

		linestream >> beat >> new_bpm;
		LOG4CXX_DEBUG(log, L"Found new bpm in line " <<
			      line_number << L" starting at beat: " <<
			      beat << L" and new bpm of " << new_bpm.get_value());
		song->new_bpm(beat, new_bpm.get_value());
	}

	void SongloadingStrategyTxt::parse_note(Song *song, wchar_t type, std::wistringstream& linestream, const int line_number)
	{
		// normal line
		int beat, length, height;
		std::wstring lyric;

		linestream >> beat >> length >> height >> std::noskipws;
		linestream.ignore();
		getline(linestream, lyric);
		boost::trim_right_if(lyric, boost::is_cntrl());

		LOG4CXX_DEBUG(log, L"Found lyric: '" << lyric << L"' at line: " << line_number <<
			      L" at beat: " << beat << L" with length: " << length <<
			      L" at height: " << height);
		song->new_note(type, beat, length, height, lyric);
	}

	Song* SongloadingStrategyTxt::load_header(const boost::filesystem::wpath& filename)
	{
		UnicodeFile file(filename);
		std::wstring line;
		std::map<std::wstring, std::wstring> header_fields;

		bool header = true, notes_found = false;
		while (file.stream().good()) {
			std::getline(file.stream(), line);

			boost::trim(line);
			boost::trim_if(line, boost::is_cntrl());
			LOG4CXX_DEBUG(log, L"Line: " << line);

			if (header && line[0] == L'#') {

				// header
				header_fields.insert(split_header_field(line));
			}
			else {
				if (header) {
					// end of header
					header = false;
				}

				if (line[0] == L':' || line[0] == L'*' || line[0] == L'F') {
					notes_found = true;
					break;
				}
			}
		}

		if (! notes_found) {
			LOG4CXX_WARN(log, L"Song: '" << filename  << L"' has no notes. Ignoring!");
			throw "No notes.";
		}

		// fill song
		return new Song(filename, header_fields);
	}
};
