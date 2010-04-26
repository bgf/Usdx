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
#include "utils/locale_independent_float.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Song::log =
		log4cxx::Logger::getLogger("usdx.base.Song");

	const boost::filesystem::wpath& Song::get_filename(void) const
	{
		return filename;
	}

	Song::Song(const boost::filesystem::wpath& filename,
		   const std::map<std::wstring, std::wstring>& header) :
		filename(filename), custom_header_tags(header)
	{
		std::map<std::wstring, std::wstring>::iterator it;

		title = get_header_tag(L"TITLE", true);
		artist = get_header_tag(L"ARTIST", true);
		mp3 = get_header_tag(L"MP3", true);

		bpm.push_back(new BPM(get_header_tag_float(L"BPM", true)));

		gap = get_header_tag_float(L"GAP");
		cover_file = get_header_tag(L"COVER");
		background = get_header_tag(L"BACKGROUND");

		video = get_header_tag(L"VIDEO");
		video_gap = get_header_tag_float(L"VIDEOGAP");

		genre = get_header_tag(L"GENRE");
		edition = get_header_tag(L"EDITION");
		creator = get_header_tag(L"CREATOR");
		language = get_header_tag(L"LANGUAGE");

		year = get_header_tag_int(L"YEAR");

		start = get_header_tag_float(L"START");
		stop = get_header_tag_int(L"END");

		resolution = get_header_tag_int(L"RESOLUTION");
		notes_gap = get_header_tag_int(L"NOTESGAP");

		relative = get_header_tag_bool(L"RELATIVE");

		// TODO
	        // EncFile := DecodeFilename(Value);
		// if (self.Path.Append(EncFile).IsFile) then
                //   self.Video := EncFile
		// else
		//  Log.LogError('Can''t find video file in song: ' +
	        // Fulfilling);

		// TODO
		// encoding = get_header_tag("ENCODING");
	}

	Song::~Song(void)
	{
		for (std::list<BPM*>::iterator it = bpm.begin(); it != bpm.end(); it++) {
			delete *it;
		}

		bpm.clear();

		for (std::list<LyricLine*>::iterator it = lyrics.begin(); it != lyrics.end(); it++) {
			delete *it;
		}
		lyrics.clear();
	}

	std::wstring Song::get_header_tag(const std::wstring& tag, const bool required)
	{
		std::map<std::wstring, std::wstring>::iterator it;
		std::wstring result = L"";

		if ((it = custom_header_tags.find(tag)) != custom_header_tags.end()) {
			result = it->second;
			custom_header_tags.erase(it);
		}
		else if (required) {
			LOG4CXX_ERROR(log, L"Incomplete Song! Missing '" << tag << L"' Tag in: '" <<
				      get_filename() << L"'");
			throw MissingTagException(tag, "Incomplete Song! Missing Tag.");
		}

		return result;
	}

	float Song::get_header_tag_float(const std::wstring& tag, const bool required)
	{
		std::map<std::wstring, std::wstring>::iterator it;
		float result;

		if ((it = custom_header_tags.find(tag)) != custom_header_tags.end()) {
			result = LocaleIndependentFloat(it->second).get_value();
			custom_header_tags.erase(it);
		}
		else if (required) {
			LOG4CXX_ERROR(log, L"Incomplete Song! Missing '" << tag << L"' Tag in: '" <<
				      get_filename() << L"'");
			throw MissingTagException(tag, "Incomplete Song! Missing Tag.");
		}

		return result;
	}

	int Song::get_header_tag_int(const std::wstring& tag, const bool required)
	{
		std::map<std::wstring, std::wstring>::iterator it;
		int result;

		if ((it = custom_header_tags.find(tag)) != custom_header_tags.end()) {
			std::wistringstream stream(it->second);
			custom_header_tags.erase(it);
			stream >> result;
		}
		else if (required) {
			LOG4CXX_ERROR(log, L"Incomplete Song! Missing '" << tag << L"' Tag in: '" <<
				      get_filename() << L"'");
			throw MissingTagException(tag, "Incomplete Song! Missing Tag.");
		}

		return result;
	}

	bool Song::get_header_tag_bool(const std::wstring& tag, const bool required)
	{
		std::map<std::wstring, std::wstring>::iterator it;
		bool result;

		if ((it = custom_header_tags.find(tag)) != custom_header_tags.end()) {
			// accept all like (YES, JA, TRUE, 1)
			result = (it->second[0] == L'j' || it->second[0] == L'J' ||
				  it->second[0] == L'y' || it->second[0] == L'Y' ||
				  it->second[0] == L't' || it->second[0] == L'T' ||
				  it->second[0] == L'1');
			custom_header_tags.erase(it);
		}
		else if (required) {
			LOG4CXX_ERROR(log, L"Incomplete Song! Missing '" << tag << L"' Tag in: '" <<
				      get_filename() << L"'");
			throw MissingTagException(tag, "Incomplete Song! Missing Tag.");
		}

		return result;
	}

	LyricLine* Song::get_last_lyric_line(void)
	{
		if (lyrics.size() > 0) {
			return lyrics.back();
		}

		return create_new_lyric_line(0);
	}

	LyricLine* Song::create_new_lyric_line(int start)
	{
		LyricLine* line = new LyricLine(start);
		lyrics.push_back(line);
		return line;
	}

	const std::wstring& Song::get_title(void) const
	{
		return title;
	}

	const std::wstring& Song::get_artist(void) const
	{
		return artist;
	}

	const std::wstring& Song::get_mp3(void) const
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

	const float Song::get_gap(void) const
	{
		return gap;
	}

	const std::wstring& Song::get_cover_file(void) const
	{
		return cover_file;
	}

	const std::wstring& Song::get_background(void) const
	{
		return background;
	}

	const std::wstring& Song::get_video(void) const
	{
		return video;
	}

	const float Song::get_video_gap(void) const
	{
		return video_gap;
	}

	const std::wstring& Song::get_genre(void) const
	{
		return genre;
	}

	const std::wstring& Song::get_edition(void) const
	{
		return edition;
	}

	const std::wstring& Song::get_creator(void) const
	{
		return creator;
	}

	const std::wstring& Song::get_language(void) const
	{
		return language;
	}

	const int Song::get_year(void) const
	{
		return year;
	}

	const float Song::get_start(void) const
	{
		return start;
	}

	const int Song::get_stop(void) const
	{
		return stop;
	}

	const int Song::get_resolution(void) const
	{
		return resolution;
	}

	const int Song::get_notes_gap(void) const
	{
		return notes_gap;
	}

	const bool Song::get_relative(void) const
	{
		return relative;
	}

	// TODO:
	// const std::string& Song::get_encoding(void) const
	// {
	// 	return encoding;
	// }

	int Song::get_relative_beat(void)
	{
		if (relative)
			return get_last_lyric_line()->get_start();

		return 0;
	}

	void Song::new_bpm(const int beat, const float new_bpm)
	{
		bpm.push_back(new BPM(beat + get_relative_beat(), new_bpm));
	}

	void Song::new_line(const int line_out, const int line_in)
	{
		get_last_lyric_line()->set_end(line_out + get_relative_beat());
		create_new_lyric_line(line_in + get_relative_beat());
	}

	void Song::new_note(const wchar_t type, const int beat, const int length, const int height, const std::wstring& lyric)
	{
		get_last_lyric_line()->add_word(new LyricWord(type, beat + get_relative_beat(), length, height, lyric));
	}

};