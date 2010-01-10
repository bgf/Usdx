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

#include "database.hpp"
#include <string.h>
#include <sstream>

namespace usdx
{
	const int db_version = 1;
	const char usdx_scores[] = "us_scores";
	const char usdx_songs[]  = "us_songs";
	const char usdx_statistics_info[] = "us_statistics_info";

	StatDatabase* StatDatabase::instance;
	log4cxx::LoggerPtr StatDatabase::log = log4cxx::Logger::getLogger("usdx.base.StatDatabase");

	StatDatabase::StatDatabase(const std::string filename)
	{
		this->filename = filename;

		if (SQLITE_OK != sqlite3_open_v2(this->filename.c_str(), &this->database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
			sqlite3_close(database);
			throw "Error opening database.";
		}
	}

	StatDatabase::~StatDatabase(void)
	{
		/* frees database */
		LOG4CXX_DEBUG(log, "Closing Database");

		sqlite3_close(database);
		database = NULL;
	}

	StatDatabase* StatDatabase::get_instance()
	{
		return instance;
	}

	sqlite3_stmt *StatDatabase::sqlite_prepare(const std::string sqlStatement)
	{
		sqlite3_stmt *sqliteStatement;
		if (SQLITE_OK != sqlite3_prepare_v2(database, sqlStatement.c_str(), sqlStatement.length(), &sqliteStatement, NULL)) {
			sqlite3_finalize(sqliteStatement);

			LOG4CXX_ERROR(log, "Error '" << sqlite3_errmsg(database) << "' in SQL '" << sqlStatement << "'");
			throw "Error preparing statement.";
		}

		return sqliteStatement;
	}

	void StatDatabase::sqlite_exec(const std::string sqlStatement)
	{
		sqlite3_stmt *sqliteStatement = sqlite_prepare(sqlStatement);
		sqlite3_step(sqliteStatement);
		sqlite3_finalize(sqliteStatement);
	}

	void StatDatabase::init(const std::string filename)
	{
		LOG4CXX_DEBUG(log, "Initializing Database: " << filename);

		instance = new StatDatabase(filename);
		// TODO
		//   // open database
		//   ScoreDB   := TSQLiteDatabase.Create(Filename.ToUTF8);
		//   fFilename := Filename;

		//   Version := GetVersion();

		//   // add Table cUS_Statistics_Info
		//   // needed in the conversion from 1.01 to 1.1
		//   if not ScoreDB.TableExists(cUS_Statistics_Info) then
		//   begin
		//     Log.LogInfo('Outdated song database found - missing table"' + cUS_Statistics_Info + '"', 'TDataBaseSystem.Init');
		//     ScoreDB.ExecSQL('CREATE TABLE IF NOT EXISTS [' + cUS_Statistics_Info + '] (' +
		//                     '[ResetTime] INTEGER' +
		//                     ');');
		//     // insert creation timestamp
		//     ScoreDB.ExecSQL(Format('INSERT INTO [' + cUS_Statistics_Info + '] ' +
		//                            '([ResetTime]) VALUES(%d);',
		//                            [DateTimeToUnix(Now())]));
		//   end;

		//   // convert data from 1.01 to 1.1
		//   // part #1 - prearrangement
		//   finalizeConversion := false;
		//   if (Version = 0) AND ScoreDB.TableExists('US_Scores') then
		//   begin
		//     // rename old tables - to be able to insert new table structures
		//     ScoreDB.ExecSQL('ALTER TABLE US_Scores RENAME TO us_scores_101;');
		//     ScoreDB.ExecSQL('ALTER TABLE US_Songs RENAME TO us_songs_101;');
		//     finalizeConversion := true; // means: conversion has to be done!
		//   end;

		//   // Set version number after creation
		//   if (Version = 0) then
		//     SetVersion(cDBVersion);

		//   // SQLite does not handle VARCHAR(n) or INT(n) as expected.
		//   // Texts do not have a restricted length, no matter which type is used,
		//   // so use the native TEXT type. INT(n) is always INTEGER.
		//   // In addition, SQLiteTable3 will fail if other types than the native SQLite
		//   // types are used (especially FieldAsInteger). Also take care to write the
		//   // types in upper-case letters although SQLite does not care about this -
		//   // SQLiteTable3 is very sensitive in this regard.
		//   ScoreDB.ExecSQL('CREATE TABLE IF NOT EXISTS [' + cUS_Scores + '] (' +
		//                     '[SongID] INTEGER NOT NULL, ' +
		//                     '[Difficulty] INTEGER NOT NULL, ' +
		//                     '[Player] TEXT NOT NULL, ' +
		//                     '[Score] INTEGER NOT NULL, ' +
		//                     '[Date] INTEGER NULL' +
		//                   ');');

		//   ScoreDB.ExecSQL('CREATE TABLE IF NOT EXISTS [' + cUS_Songs + '] (' +
		//                     '[ID] INTEGER PRIMARY KEY, ' +
		//                     '[Artist] TEXT NOT NULL, ' +
		//                     '[Title] TEXT NOT NULL, ' +
		//                     '[TimesPlayed] INTEGER NOT NULL, ' +
		//                     '[Rating] INTEGER NULL' +
		//                   ');');

		//   // convert data from 1.01 to 1.1
		//   // part #2 - accomplishment
		//   if finalizeConversion then
		//   begin
		//     Log.LogInfo('Outdated song database  found - begin conversion from V1.01 to V1.1', 'TDataBaseSystem.Init');
		//     // insert old values into new db-schemes (/tables)
		//     ScoreDB.ExecSQL('INSERT INTO ' + cUS_Scores + ' SELECT  SongID, Difficulty, Player, Score FROM us_scores_101;');
		//     ScoreDB.ExecSQL('INSERT INTO ' + cUS_Songs + ' SELECT  ID, Artist, Title, TimesPlayed, ''NULL'' FROM us_songs_101;');
		//     //now drop old tables
		//     ScoreDB.ExecSQL('DROP TABLE us_scores_101;');
		//     ScoreDB.ExecSQL('DROP TABLE us_songs_101;');
		//   end;

		//   // add column rating to cUS_Songs
		//   // just for users of nightly builds and developers!
		//   if not ScoreDB.ContainsColumn(cUS_Songs, 'Rating') then
		//   begin
		//     Log.LogInfo('Outdated song database found - adding column rating to "' + cUS_Songs + '"', 'TDataBaseSystem.Init');
		//     ScoreDB.ExecSQL('ALTER TABLE ' + cUS_Songs + ' ADD COLUMN [Rating] INTEGER NULL');
		//   end;


		//   //add column date to cUS-Scores
		//   if not ScoreDB.ContainsColumn(cUS_Scores, 'Date') then
		//   begin
		//     Log.LogInfo('adding column date to "' + cUS_Scores + '"', 'TDataBaseSystem.Init');
		//     ScoreDB.ExecSQL('ALTER TABLE ' + cUS_Scores + ' ADD COLUMN [Date] INTEGER NULL');
		//   end;

		// except
		//   on E: Exception do
		//   begin
		//     Log.LogError(E.Message, 'TDataBaseSystem.Init');
		//     FreeAndNil(ScoreDB);
		//   end;
		// end;

	}

	int StatDatabase::get_version(void)
	{
		int result = -1;
		sqlite3_stmt *sqliteStatement = sqlite_prepare("PRAGMA user_version;");

		int rc = sqlite3_step(sqliteStatement);
		if (rc == SQLITE_ROW) {
			result = sqlite3_column_int(sqliteStatement, 0);
		}

		sqlite3_finalize(sqliteStatement);
		return result;
	}

	void StatDatabase::set_version(int version)
	{
		// format the PRAGMA statement (PRAGMA does _not_ support parameters)
		std::ostringstream sqlStatementBuffer (std::ostringstream::out);
		sqlStatementBuffer << "PRAGMA user_version = " << version << ";";

		sqlite_exec(sqlStatementBuffer.str());
	}

/*	void StatDatabase::read_score(Song *song)
	{
		// TODO
		// var
		//   TableData:  TSQLiteUniTable;
		//   Difficulty: integer;
		//   I: integer;
		//   PlayerListed: boolean;
		// begin
		//   if not Assigned(ScoreDB) then
		//     Exit;

		//   TableData := nil;
		//   try
		//     // Search Song in DB
		//     TableData := ScoreDB.GetUniTable(
		//       'SELECT [Difficulty], [Player], [Score], [Date] FROM [' + cUS_Scores + '] ' +
		//       'WHERE [SongID] = (' +
		//         'SELECT [ID] FROM [' + cUS_Songs + '] ' +
		//         'WHERE [Artist] = ? AND [Title] = ? ' +
		//         'LIMIT 1) ' +
		//       'ORDER BY [Score] DESC;', //no LIMIT! see filter below!
		//       [Song.Artist, Song.Title]);

		//     // Empty Old Scores
		//     SetLength(Song.Score[0], 0); //easy
		//     SetLength(Song.Score[1], 0); //medium
		//     SetLength(Song.Score[2], 0); //hard

		//     // Go through all Entrys
		//     while (not TableData.EOF) do
		//     begin
		//       // Add one Entry to Array
		//       Difficulty := TableData.FieldAsInteger(TableData.FieldIndex['Difficulty']);
		//       if ((Difficulty >= 0) and (Difficulty <= 2)) and
		//          (Length(Song.Score[Difficulty]) < 5) then
		//       begin
		//         //filter player
		//         PlayerListed:=false;
		//         if (Length(Song.Score[Difficulty])>0) then
		//         begin
		//           for I := 0 to Length(Song.Score[Difficulty]) - 1 do
		//           begin
		//             if (Song.Score[Difficulty, I].Name = TableData.FieldByName['Player']) then
		//             begin
		//               PlayerListed:=true;
		//               break;
		//             end;
		//           end;
		//         end;

		//         if not PlayerListed then
		//         begin
		//           SetLength(Song.Score[Difficulty], Length(Song.Score[Difficulty]) + 1);

		//           Song.Score[Difficulty, High(Song.Score[Difficulty])].Name  :=
		//             TableData.FieldByName['Player'];
		//           Song.Score[Difficulty, High(Song.Score[Difficulty])].Score :=
		//             TableData.FieldAsInteger(TableData.FieldIndex['Score']);
		//           Song.Score[Difficulty, High(Song.Score[Difficulty])].Date :=
		//             FormatDate(TableData.FieldAsInteger(TableData.FieldIndex['Date']));
		//         end;
		//       end;

		//       TableData.Next;
		//     end; // while

		//   except
		//     for Difficulty := 0 to 2 do
		//     begin
		//       SetLength(Song.Score[Difficulty], 1);
		//       Song.Score[Difficulty, 1].Name := 'Error Reading ScoreDB';
		//     end;
		//   end;

		//   TableData.Free;
	}

	void StatDatabase::add_score(Song *song, int level, const char* name, int score)
	{
		// TODO
		// var
		//   ID:        integer;
		//   TableData: TSQLiteTable;
		// begin
		//   if not Assigned(ScoreDB) then
		//     Exit;

		//   // Prevent 0 Scores from being added EDIT: ==> UScreenTop5.pas!
		//   //if (Score <= 0) then
		//   //  Exit;

		//   TableData := nil;

		//   try

		//     ID := ScoreDB.GetTableValue(
		//         'SELECT [ID] FROM [' + cUS_Songs + '] ' +
		//         'WHERE [Artist] = ? AND [Title] = ?',
		//         [Song.Artist, Song.Title]);
		//     if (ID = 0) then
		//     begin
		//       // Create song if it does not exist
		//       ScoreDB.ExecSQL(
		//           'INSERT INTO [' + cUS_Songs + '] ' +
		//           '([ID], [Artist], [Title], [TimesPlayed]) VALUES ' +
		//           '(NULL, ?, ?, 0);',
		//           [Song.Artist, Song.Title]);
		//       // Get song-ID
		//       ID := ScoreDB.GetLastInsertRowID();
		//     end;
		//     // Create new entry
		//     ScoreDB.ExecSQL(
		//       'INSERT INTO [' + cUS_Scores + '] ' +
		//       '([SongID] ,[Difficulty], [Player], [Score], [Date]) VALUES ' +
		//       '(?, ?, ?, ?, ?);',
		//       [ID, Level, Name, Score, DateTimeToUnix(Now())]);

		//   except on E: Exception do
		//     Log.LogError(E.Message, 'TDataBaseSystem.AddScore');
		//   end;

		//   TableData.Free;
 	}

	void StatDatabase::write_score(Song *song)
	{
		// TODO
		// if not Assigned(ScoreDB) then
		//   Exit;

		// try
		//   // Increase TimesPlayed
		//   ScoreDB.ExecSQL(
		//       'UPDATE [' + cUS_Songs + '] ' +
		//       'SET [TimesPlayed] = [TimesPlayed] + 1 ' +
		//       'WHERE [Title] = ? AND [Artist] = ?;',
		//       [Song.Title, Song.Artist]);
		// except on E: Exception do
		//   Log.LogError(E.Message, 'TDataBaseSystem.WriteScore');
		// end;
	}

*/
	const std::string StatDatabase::get_filename(void)
	{
		return this->filename;
	}


	StatResult* StatDatabase::get_stats(StatResult *list, short count, unsigned int page, bool reversed)
	{
		// TODO
		return NULL;
	}

/*	unsigned int StatDatabase::get_total_entrys(StatType type)
	{
		// TODO
		// var
		//   Query: string;
		// begin
		//   Result := 0;

		//   if not Assigned(ScoreDB) then
		//     Exit;

		//   try
		//     // Create query
		//     case Typ of
		//       stBestScores:
		//         Query := 'SELECT COUNT([SongID]) FROM [' + cUS_Scores + '];';
		//       stBestSingers:
		//         Query := 'SELECT COUNT(DISTINCT [Player]) FROM [' + cUS_Scores + '];';
		//       stMostSungSong:
		//         Query := 'SELECT COUNT([ID]) FROM [' + cUS_Songs + '];';
		//       stMostPopBand:
		//         Query := 'SELECT COUNT(DISTINCT [Artist]) FROM [' + cUS_Songs + '];';
		//     end;

		//     Result := ScoreDB.GetTableValue(Query);
		//   except on E: Exception do
		//     Log.LogError(E.Message, 'TDataBaseSystem.GetTotalEntrys');
		//   end;
	}
*/
	time_t StatDatabase::get_stat_reset(void)
	{
		int result = -1;

		std::string sqlStatement = "SELECT [ResetTime] FROM [";
		sqlStatement += usdx_statistics_info;
		sqlStatement += "];";

		sqlite3_stmt *sqliteStatement = sqlite_prepare(sqlStatement);

		int rc = sqlite3_step(sqliteStatement);
		if (rc == SQLITE_ROW) {
			result = sqlite3_column_int(sqliteStatement, 0);
		}

		sqlite3_finalize(sqliteStatement);
		return (time_t)result;
	}

	char* StatDatabase::format_date(char* time, size_t max, time_t timestamp)
	{
		if (timestamp != 0) {
			struct tm tmp;

			if (localtime_r(&timestamp, &tmp)) {
				strftime(time, max, "%d.%m.%y" /* TODO: Language.Translate("STAT_FORMAT_DATE")*/, &tmp);
				return time;
			}
		}

		if (max > 0) {
			time[0] = '\0';
			return time;
		}

		return NULL;
	}

	/* recursive delete the list items */
	StatResult::~StatResult(void)
	{
		if (this->next) {
			delete this->next;
			this->next = NULL;
		}
	}
};
