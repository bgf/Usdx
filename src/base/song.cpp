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
#include "lyric_word.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Song::log =
		log4cxx::Logger::getLogger("usdx.base.Song");

	const std::string& Song::get_filename(void) const
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
		// TODO
		// bpm.push_back(new BPM(get_header_tag("BPM", true)));

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

	Song::~Song(void)
	{
		bpm.clear();
		lyrics.clear();
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

	LyricLine* Song::get_last_lyric_line(void)
	{
		LyricLine* line = lyrics.back();

		if (line) {
			return line;
		}

		return create_new_lyric_line(0);
	}

	LyricLine* Song::create_new_lyric_line(int start)
	{
		LyricLine* line = new LyricLine(start);
		lyrics.push_back(line);
		return line;
	}

	const std::string& Song::get_title(void) const
	{
		return title;
	}

	const std::string& Song::get_artist(void) const
	{
		return artist;
	}

	const std::string& Song::get_mp3(void) const
	{
		return mp3;
	}

	const float Song::get_bpm(int beat) const
	{
		float last_bpm;

		for (std::list<BPM*>::const_iterator it = bpm.begin(); it != bpm.end(); it++) {
			if ((*it)->get_beat() > beat) {
				break;
			}

			last_bpm = (*it)->get_bpm();
		}

		return last_bpm;
	}

	// TODO
	// const float Song::get_gap(void) const
	// {
	// 	return gap;
	// }

	const std::string& Song::get_cover(void) const
	{
		return cover;
	}

	const std::string& Song::get_background(void) const
	{
		return background;
	}

	const std::string& Song::get_video(void) const
	{
		return video;
	}

	// TODO
	// const float Song::get_videogap(void) const
	// {
	// 	return videogap;
	// }

	const std::string& Song::get_genre(void) const
	{
		return genre;
	}

	const std::string& Song::get_edition(void) const
	{
		return edition;
	}

	const std::string& Song::get_creator(void) const
	{
		return creator;
	}

	const std::string& Song::get_language(void) const
	{
		return language;
	}

	// TODO
	// const int Song::get_year(void) const
	// {
	// 	return year;
	// }

	// TODO
	// const float Song::get_start(void) const
	// {
	// 	return start;
	// }

	// TODO
	// const int Song::get_end(void) const
	// {
	// 	return end;
	// }

	// TODO
	// const int Song::get_resolution(void) const
	// {
	// 	return resolution;
	// }

	// TODO
	// const int Song::get_notesgap(void) const
	// {
	// 	return notesgap;
	// }

	// TODO
	// const bool Song::get_relative(void) const
	// {
	// 	return relative;
	// }

	// TODO: filetype
	// const std::string& Song::get_encoding(void) const
	// {
	// 	return encoding;
	// }

	void Song::new_bpm(const int beat, const float new_bpm)
	{
		bpm.push_back(new BPM(beat, new_bpm));
	}

	void Song::new_line(const int line_out, const int line_in)
	{
		get_last_lyric_line()->set_end(line_out);
		create_new_lyric_line(line_in);
	}

	void Song::new_note(const char type, const int beat, const int length, const int height, const std::string& lyric)
	{
		get_last_lyric_line()->add_word(new LyricWord(type, beat, length, height, lyric));
	}

};
