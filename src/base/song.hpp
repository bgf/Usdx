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
#include <list>
#include <boost/filesystem.hpp>
#include <log4cxx/logger.h>
#include "bpm.hpp"
#include "lyric_line.hpp"
#include "utils/base_exception.hpp"

namespace usdx
{
	class MissingTagException : public BaseException
	{
	private:
		/**
		 * TODO: Maybe refactor this to separate sub-classes.
		 */
		const std::wstring tag;

	public:
		MissingTagException(const std::wstring tag,
				    const std::string message) :
			BaseException(message), tag(tag) {};

		~MissingTagException () throw () {};

		virtual const std::wstring& get_tag() const { return tag; };
	};

	class Song
	{
	private:
		static log4cxx::LoggerPtr log;

		boost::filesystem::wpath filename;

		std::wstring title;
		std::wstring artist;

		// filenames
		std::wstring mp3;

		std::wstring background;

		std::wstring video;
		float video_gap;

		std::wstring cover;
		// texture cover_tex;

		std::wstring genre;
		std::wstring edition;
		std::wstring language;
		int year;
		std::wstring creator;

		int notes_gap;
		float gap; ///< in miliseconds

		float start; ///< in seconds
		int stop; ///< in miliseconds
		bool relative;
		int resolution;

		std::list<BPM*> bpm;

		std::list<LyricLine*> lyrics;

		std::map<std::wstring, std::wstring> custom_header_tags;

		std::wstring get_header_tag(const std::wstring& tag, const bool required = false);
		float get_header_tag_float(const std::wstring& tag, const bool required = false);
		int get_header_tag_int(const std::wstring& tag, const bool required = false);
		bool get_header_tag_bool(const std::wstring& tag, const bool required = false);

		LyricLine* get_last_lyric_line(void);
		LyricLine* create_new_lyric_line(int start);

		/**
		 * Used to calculate the absolute beat times in relative song
		 * mode.
		 *
		 * @return Start beat time from last line.
		 */
		int get_relative_beat(void);

		// TODO: Encoding:   TEncoding;
	public:
		Song(const boost::filesystem::wpath& filename,
		     const std::map<std::wstring, std::wstring>& header);

		virtual ~Song(void);

		const boost::filesystem::wpath& get_filename(void) const;

		const std::wstring& get_title(void) const;
		const std::wstring& get_artist(void) const;
		const std::wstring& get_mp3(void) const;
		const float get_bpm(int beat) const;
		const float get_gap(void) const;
		const std::wstring& get_cover(void) const;
		const std::wstring& get_background(void) const;
		const std::wstring& get_video(void) const;
		const float get_video_gap(void) const;
		const std::wstring& get_genre(void) const;
		const std::wstring& get_edition(void) const;
		const std::wstring& get_creator(void) const;
		const std::wstring& get_language(void) const;
		const int get_year(void) const;
		const float get_start(void) const;
		const int get_stop(void) const;
		const int get_resolution(void) const;
		const int get_notes_gap(void) const;
		const bool get_relative(void) const;

		// TODO: encoding class
		// const std::string& get_encoding(void) const;

		void new_bpm(const int beat, const float new_bpm);
		void new_line(const int line_out, const int line_in);
		void new_note(const wchar_t type, const int beat, const int length, const int height, const std::wstring& lyric);
	};
};

#endif
