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

#include "song.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Song::log =
		log4cxx::Logger::getLogger("usdx.base.Song");

	const std::string& Song::get_filename(void)
	{
		return filename;
	}

	Song::Song(const std::string& filename, const std::map<std::string, std::string>& header) :
		filename(filename), custom_header_tags(header)
	{
		std::map<std::string, std::string>::iterator it;

		title = get_header_tag("TITLE", true);
		artist = get_header_tag("ARTIST", true);
		mp3 = get_header_tag("MP3", true);
		bpm = get_header_tag("BPM", true);

		// TODO: float
		// gap = get_header_tag("GAP");
		cover = get_header_tag("COVER");
		background = get_header_tag("BACKGROUND");

		video = get_header_tag("VIDEO");
		// TODO
	        // EncFile := DecodeFilename(Value);
		// if (self.Path.Append(EncFile).IsFile) then
                //   self.Video := EncFile
		// else
		//  Log.LogError('Can''t find video file in song: ' +
	        // Fulfilling);

		// TODO: float
		// videogap = get_header_tag("VIDEOGAP");

		genre = get_header_tag("GENRE");
		edition = get_header_tag("EDITION");
		creator = get_header_tag("CREATOR");
		language = get_header_tag("LANGUAGE");

		// TODO: int
		// year = get_header_tag("YEAR");

		// TODO: float
		// start = get_header_tag("START");

		// TODO: int
		// end = get_header_tag("END");
		// resolution = get_header_tag("RESOLUTION");
		// notesgap = get_header_tag("NOTESGAP");

		// TODO: bool
		// relative = get_header_tag("RELATIVE");

		// TODO
		// encoding = get_header_tag("ENCODING");
	}

	std::string Song::get_header_tag(const std::string& tag, const bool required)
	{
		std::map<std::string, std::string>::iterator it;
		std::string result = "";

		if ((it = custom_header_tags.find(tag)) != custom_header_tags.end()) {
			result = it->second;
			custom_header_tags.erase(it);
		}
		else if (required) {
			LOG4CXX_ERROR(log, "Incomplete Song! Missing '" << tag << "' Tag in: '" << get_filename() << "'");
			throw "Incomplete Song! Missing Tag.";
		}

		return result;
	}

	const std::string& Song::get_title(void)
	{
		return title;
	}

	const std::string& Song::get_artist(void)
	{
		return artist;
	}
};
