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

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <log4cxx/logger.h>

namespace usdx
{
	class StatResult;

	/* Wrapper for statistic database */
	class StatDatabase
	{
	private:
		static log4cxx::LoggerPtr log;

		std::string filename;
		sqlite3 *database;

		// Singleton
		StatDatabase(std::string filename);

		static StatDatabase* instance;

		int get_version(void);
		void set_version(int version);

#ifdef STAT_DATABASE_TEST
		// for testing private members
		friend class StatDatabaseTest;
#endif

	public:
		static StatDatabase* get_instance();

		~StatDatabase(void);

		static void init(const std::string filename);

/*		void read_score(Song *song);
		void add_score(Song *song, int level, const char* name, int score);
		void write_score(Song *song);
*/
		const std::string get_filename(void);

		StatResult* get_stats(StatResult *list, short count, unsigned int page, bool reversed);
//		unsigned int get_total_entrys(StatType type);

		time_t get_stat_reset(void);
		char* format_date(char* time, size_t max, time_t timestamp);
	};

	/* Element for linked list with pointer to next */
	class StatResult
	{
	private:
		StatResult() {};
		StatResult(const StatResult &source) {};
		void operator=(const StatResult &source) {};

	protected:
		StatResult *next;

	public:
		virtual ~StatResult(void);
	};

	class StatResultBestScores : StatResult
	{
	private:
		char *singer;
		unsigned short score;
		unsigned short difficulty;
		char *song_artist;
		char *song_title;
		time_t date;

	public:
		StatResultBestScores(
			char *singer,
			unsigned short score,
			unsigned short difficulty,
			char* song_artist,
			char* song_title,
			time_t date);
		~StatResultBestScores(void);
	};

	class StatResultBestSingers : StatResult
	{
	private:
		char *singer;
		unsigned short average_score;

	public:
		StatResultBestSingers(char *singer, unsigned short average_score);
		~StatResultBestSingers(void);
	};

	class StatResultMostSungSong : StatResult
	{
	private:
		char *song_artist;
		char *song_title;
		unsigned short times_sung;

	public:
		StatResultMostSungSong(char* song_artist, char* song_title, unsigned short times_sung);
		~StatResultMostSungSong(void);
	};

	class StatResultMostSungBand : StatResult
	{
	private:
		char *song_artist;
		unsigned short times_sung;

	public:
		StatResultMostSungBand(char* song_artist, unsigned short times_sung);
		~StatResultMostSungBand(void);
	};
};

#endif
