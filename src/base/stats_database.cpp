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

#include "stats_database.hpp"

namespace usdx
{
	const int db_version = 1;
	const std::wstring StatDatabase::usdx_scores =
		L"us_scores";

	const std::wstring StatDatabase::usdx_songs  =
		L"us_songs";

	const std::wstring StatDatabase::usdx_statistics_info =
		L"us_statistics_info";

	log4cxx::LoggerPtr StatDatabase::log =
		log4cxx::Logger::getLogger("usdx.base.StatDatabase");

	StatDatabase::StatDatabase(const std::string filename) :
		Database(filename)
	{
		LOG4CXX_DEBUG(log, "Initializing Database: " << filename);

		if (! sqlite_table_exists(usdx_statistics_info)) {
			// add table usdx_statistics_info, needed in the
			// conversion from 1.01 to 1.1
			LOG4CXX_INFO(log, L"Outdated song database found " <<
				     L"- missing table'" <<
				     usdx_statistics_info << L"'");

			sqlite_exec(L"CREATE TABLE IF NOT EXISTS [" +
				    usdx_statistics_info +
				    L"] ([ResetTime] Integer);");

			// insert creation timestamp
			sqlite3_stmt *sqliteStatement =
				sqlite_prepare(L"INSERT INTO [" +
					       usdx_statistics_info +
					       L"] ([ResetTime]) VALUES (?1);");

			sqlite3_bind_int(sqliteStatement, 1, time(NULL));
			sqlite3_step(sqliteStatement);
			sqlite3_finalize(sqliteStatement);
		}

		int version = get_version();

		bool finalizeConversion = false;
		if (version == 0 && sqlite_table_exists(L"US_Scores")) {
			// convert data from 1.01 to 1.1
			// part #1 - prearrangement: rename old tables
			// to be able to insert new table structures
			sqlite_exec(L"ALTER TABLE US_Scores RENAME TO us_scores_101;");
			sqlite_exec(L"ALTER TABLE US_Songs RENAME TO us_songs_101;");
		}

		if (version == 0) {
			// Set version number after creation
			set_version(db_version);
		}

		// SQLite does not handle VARCHAR(n) or INT(n) as expected.
		// Texts do not have a restricted length, no matter which type
		// is used, so use the native TEXT type. INT(n) is always
		// INTEGER.  In addition, SQLiteTable3 will fail if other types
		// than the native SQLite types are used (especially
		// FieldAsInteger). Also take care to write the types in
		// upper-case letters although SQLite does not care about this -
		// SQLiteTable3 is very sensitive in this regard.
		std::wstring sqlStatement;

		sqlStatement = L"CREATE TABLE IF NOT EXISTS [";
		sqlStatement += usdx_scores;
		sqlStatement += L"] (";
		sqlStatement += L"[SongID] INTEGER NOT NULL, ";
		sqlStatement += L"[Difficulty] INTEGER NOT NULL, ";
		sqlStatement += L"[Player] TEXT NOT NULL, ";
		sqlStatement += L"[Score] INTEGER NOT NULL, ";
		sqlStatement += L"[Date] INTEGER NULL";
		sqlStatement += L");";

		sqlite_exec(sqlStatement);

		sqlStatement = L"CREATE TABLE IF NOT EXISTS [";
		sqlStatement += usdx_songs;
		sqlStatement += L"] (";
		sqlStatement += L"[ID] INTEGER PRIMARY KEY, ";
		sqlStatement += L"[Artist] TEXT NOT NULL, ";
		sqlStatement += L"[Title] TEXT NOT NULL, ";
		sqlStatement += L"[TimesPlayed] INTEGER NOT NULL, ";
		sqlStatement += L"[Rating] INTEGER NULL";
		sqlStatement += L");";

		sqlite_exec(sqlStatement);

		if (finalizeConversion) {
			// convert data from 1.01 to 1.1
			// part #2 - accomplishment
			LOG4CXX_INFO(log, L"Outdated song database found - " <<
				     L"begin conversion from V1.01 to V1.1");

			// insert old values into new db-schemes (/tables)
			sqlStatement = L"INSERT INTO [";
			sqlStatement += usdx_scores;
			sqlStatement += L"] SELECT  [SongID], ";
			sqlStatement += L"[Difficulty], [Player], ";
			sqlStatement += L"[Score] FROM [us_scores_101];";
			sqlite_exec(sqlStatement);

			sqlStatement = L"INSERT INTO [";
			sqlStatement += usdx_songs;
			sqlStatement += L"]  SELECT  [ID], [Artist], ";
			sqlStatement += L"[Title], [TimesPlayed], NULL ";
			sqlStatement += L"FROM [us_songs_101];";
			sqlite_exec(sqlStatement);

			// now drop old tables
			sqlite_exec(L"DROP TABLE us_scores_101;");
			sqlite_exec(L"DROP TABLE us_songs_101;");
		}

		// add column rating to cUS_Songs
		// just for users of nightly builds and developers!
		if (! sqlite_table_contains_column(usdx_songs, L"Rating")) {
			LOG4CXX_INFO(log, L"Outdated song database found - " <<
				     L"adding column rating to '" <<
				     usdx_songs << L"'");

			sqlite_exec(L"ALTER TABLE [" + usdx_songs +
				    L"] ADD COLUMN [Rating] INTEGER NULL;");
		}

		//add column date to cUS-Scores
		if (! sqlite_table_contains_column(usdx_scores, L"Date")) {
			LOG4CXX_INFO(log, L"Outdated score database found - " <<
				     L"adding column date to '" <<
				     usdx_scores << L"'");

			sqlite_exec(L"ALTER TABLE [" + usdx_scores +
				    L"] ADD COLUMN [Date] INTEGER NULL;");
		}
	}

	StatDatabase::~StatDatabase(void)
	{
		this->Database::~Database();
	}

	char* StatDatabase::format_date(char* time,
					size_t max,
					time_t timestamp)
	{
		if (timestamp != 0) {
			struct tm tmp;

			if (localtime_r(&timestamp, &tmp)) {
				strftime(time, max, "%d.%m.%y"
					 /* TODO: Language.Translate("STAT_FORMAT_DATE")*/,
					 &tmp);
				return time;
			}
		}

		if (max > 0) {
			time[0] = '\0';
			return time;
		}

		return NULL;
	}
};
