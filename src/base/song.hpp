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

#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <map>
#include <log4cxx/logger.h>

namespace usdx
{
	class Song
	{
	private:
		static log4cxx::LoggerPtr log;

		std::string filename;

		std::string title;
		std::string artist;

		// filenames
		std::string mp3;

		std::string background;

		std::string video;
		float video_gap;

		std::string cover;
		// texture cover_tex;

		std::string genre;
		std::string edition;
		std::string language;
		std::string year;
		std::string creator;

		int notes_gap;
		float gap; // in miliseconds

		float start; // in seconds
		int finish; // in miliseconds
		bool relative;
		int resolution;
		// TODO: bpm: array of TBPM
		std::string bpm;

		// TODO: list of LyricLines

		// TODO: Encoding:   TEncoding;
		std::map<std::string, std::string> custom_header_tags;

		std::string get_header_tag(const std::string& tag, const bool required = false);
	public:
		const std::string& get_filename(void);

		Song(const std::string& filename, const std::map<std::string, std::string>& header);

		const std::string& get_title(void);
		const std::string& get_artist(void);
		const std::string& get_mp3(void);
		// TODO: bpm array
		//const bpmarray get_bpm(void);
		//const float get_gap(void);
		const std::string& get_cover(void);
		const std::string& get_background(void);
		const std::string& get_video(void);
		//const float get_videogap(void);
		const std::string& get_genre(void);
		const std::string& get_edition(void);
		const std::string& get_creator(void);
		const std::string& get_language(void);
		//const int get_year(void);
		//const float get_start(void);
		//const int get_end(void);
		//const int get_resolution(void);
		//const int get_notesgap(void);
		//const bool get_relative(void);
		// TODO: encodeing class
		//const std::string& get_encoding(void);
	};
};

#endif
