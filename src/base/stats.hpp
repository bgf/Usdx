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

#ifndef STATS_HPP
#define STATS_HPP

#include <string>
#include <log4cxx/logger.h>
#include "stats_database.hpp"

namespace usdx
{
	/**
	 * Virtual base class for all different statistics.
	 */
	class Stats
	{
	private:
		static log4cxx::LoggerPtr log;

		static StatDatabase *db;
		static std::string filename;

	protected:
		/**
		 * Get the current StatDatabase object for making sqlite
		 * operations. On first execution after setting a filename, the
		 * database is open and initialized. If no filename was set an
		 * exception will be thrown. This function tries to ensure, that
		 * there is only one instance of StatDatabase. (not thread safe)
		 *
		 * @see set_filename(std::string filename)
		 * @return pointer to the StatDatabase object
		 */
		static StatDatabase *get_database(void);

		Stats(void) {};

		/**
		 * Abstract virtual deconstructor. This is here to be able to
		 * delete all subclasses correctly even if there is only a Stats
		 * pointer.
		 */
		virtual ~Stats(void) {};

		/**
		 * TODO
		 */
		static int get_count(std::string query);

	public:
		/**
		 * Get the timestamp of the last reset of the database.
 		 *
		 * @return Timestamp
		 */
		time_t get_stat_reset(void);

		/**
		 * Set the filename of the file to use as statistic
		 * database. The filename has to be set before executing the
		 * get_database member function. If this function is called, the
		 * current statistic database is closed and a new with the given
		 * filename will be open on next access.
		 *
		 * @param filename Filename to use as statistic database.
		 */
		static void set_filename(std::string filename);

		/**
		 * Get the filename used as statistic database.
		 *
		 * @return Filename of the statistics database.
		 */
		static std::string get_filename();

		/**
		 * TODO
		 */
//		static void add_score(Song *song, int level, const char* player, int score);

		/**
		 * TODD
		 */
//		static void add_song(Song *song);
	};

	class StatResultBestScores : public Stats
	{
	private:
		std::string singer;
		unsigned short score;
		unsigned short difficulty;
		std::string song_artist;
		std::string song_title;
		time_t date;

		StatResultBestScores *next;

		StatResultBestScores(
			char *singer,
			unsigned short score,
			unsigned short difficulty,
			char* song_artist,
			char* song_title,
			time_t date);
	public:
		/**
		 * TODO
		 */
		StatResultBestScores(char* song_artist, char* song_title);

		~StatResultBestScores(void);

		static int get_count(void);
		static StatResultBestScores *get_stats();

		StatResultBestScores *get_next();
	};


	class StatResultBestSingers : public Stats
	{
	private:
		std::string singer;
		unsigned short average_score;

		StatResultBestSingers *next;

		StatResultBestSingers(char *singer, unsigned short average_score);
	public:
		~StatResultBestSingers(void);

		static int get_count(void);
		static StatResultBestSingers *get_stats();

		StatResultBestSingers *get_next();
	};


	class StatResultMostSungSong : public Stats
	{
	private:
		std::string song_artist;
		std::string song_title;
		unsigned short times_sung;

		StatResultMostSungSong *next;

		StatResultMostSungSong(char* song_artist, char* song_title, unsigned short times_sung);
	public:
		~StatResultMostSungSong(void);

		static int get_count(void);
		static StatResultMostSungSong *get_stats();

		StatResultMostSungSong *get_next();
	};


	class StatResultMostSungBand : public Stats
	{
	private:
		std::string song_artist;
		unsigned short times_sung;

		StatResultMostSungBand *next;

		StatResultMostSungBand(char* song_artist, unsigned short times_sung);
	public:
		~StatResultMostSungBand(void);

		static int get_count(void);
		static StatResultMostSungBand *get_stats();

		StatResultMostSungBand *get_next();
	};
};

#endif
