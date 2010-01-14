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

#include "stats.hpp"

namespace usdx
{
	StatDatabase *Stats::db = NULL;
	std::string Stats::filename = std::string("");

	log4cxx::LoggerPtr Stats::log =
		log4cxx::Logger::getLogger("usdx.base.Stats");

	StatDatabase *Stats::get_database(void)
	{
		if (filename == "")
		{
			LOG4CXX_ERROR(log, "You have to set a filename first.");
			throw "You have to set a filename first.";
		}

		if (db == NULL) {
			db = new StatDatabase(filename);
		}

		return db;
	}

	int Stats::get_count(std::string query)
	{
		int result = 0;
		sqlite3_stmt *sqliteStatement =
			get_database()->sqlite_prepare(query);

		int rc = sqlite3_step(sqliteStatement);
		if (rc == SQLITE_ROW) {
			result = sqlite3_column_int(sqliteStatement, 0);
		}

		sqlite3_finalize(sqliteStatement);
		return result;

	}

	void Stats::set_filename(std::string filename)
	{
		Stats::filename = filename;

		// close old database
		delete db;
		db = NULL;
	}

	std::string Stats::get_filename(void)
	{
		return filename;
	}

	time_t Stats::get_stat_reset(void)
	{
		int result = -1;

		sqlite3_stmt *sqliteStatement = get_database()->sqlite_prepare(
			"SELECT [ResetTime] FROM [" +
			get_database()->usdx_statistics_info + "];");

		int rc = sqlite3_step(sqliteStatement);
		if (rc == SQLITE_ROW) {
			result = sqlite3_column_int(sqliteStatement, 0);
		}

		sqlite3_finalize(sqliteStatement);
		return (time_t)result;
	}

/*	void Stats::add_score(Song *song, int level, const char* player, int score)
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
*/

/*	void Stats::add_song(Song *song)
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

	StatResultBestScores::StatResultBestScores(char *singer, unsigned short score, unsigned short difficulty,
		char* song_artist, char* song_title, time_t date)
	{
		this->singer = std::string(singer);
		this->score = score;
		this->difficulty = difficulty;
		this->song_artist = std::string(song_artist);
		this->song_title = std::string(song_title);
		this->date = date;
		this->next = NULL;
	}

	StatResultBestScores::StatResultBestScores(char* song_artist, char* song_title)
	{
		this->next = NULL;

		// get score for this song from db
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

	StatResultBestScores::~StatResultBestScores(void)
	{
		if (next) {
			delete next;
			next = NULL;
		}
	}

	StatResultBestScores *StatResultBestScores::get_next()
	{
		return next;
	}

	int StatResultBestScores::get_count(void)
	{
		return Stats::get_count("SELECT COUNT([SongID]) FROM [" +
					get_database()->usdx_scores + "];");
	}

	StatResultBestScores *StatResultBestScores::get_stats()
	{
		// TODO
		return NULL;
	}



	StatResultBestSingers::StatResultBestSingers(char *singer, unsigned short average_score)
	{
		this->singer = std::string(singer);
		this->average_score = average_score;
		this->next = NULL;
	}

	StatResultBestSingers::~StatResultBestSingers(void)
	{
		if (next) {
			delete next;
			next = NULL;
		}
	}

	StatResultBestSingers *StatResultBestSingers::get_next()
	{
		return next;
	}

	int StatResultBestSingers::get_count(void)
	{
		return Stats::get_count(
			"SELECT COUNT(DISTINCT [Player]) FROM ["
			+ get_database()->usdx_scores + "];");
	}

	StatResultBestSingers *StatResultBestSingers::get_stats()
	{
		// TODO
		return NULL;
	}


	StatResultMostSungSong::StatResultMostSungSong(char* song_artist, char* song_title, unsigned short times_sung)
	{
		this->song_artist = std::string(song_artist);
		this->song_title = std::string(song_title);
		this->times_sung = times_sung;
		this->next = NULL;
	}

	StatResultMostSungSong::~StatResultMostSungSong(void)
	{
		if (next) {
			delete next;
			next = NULL;
		}
	}

	StatResultMostSungSong *StatResultMostSungSong::get_next()
	{
		return next;
	}

	int StatResultMostSungSong::get_count(void)
	{
		return Stats::get_count("SELECT COUNT([ID]) FROM [" +
					get_database()->usdx_scores + "];");
	}

	StatResultMostSungSong *StatResultMostSungSong::get_stats()
	{
		// TODO
		return NULL;
	}


	StatResultMostSungBand::StatResultMostSungBand(char* song_artist, unsigned short times_sung)
	{
		this->song_artist = std::string(song_artist);
		this->times_sung = times_sung;
		this->next = NULL;
	}

	StatResultMostSungBand::~StatResultMostSungBand(void)
	{
		if (next) {
			delete next;
			next = NULL;
		}
	}

	StatResultMostSungBand *StatResultMostSungBand::get_next()
	{
		return next;
	}

	int StatResultMostSungBand::get_count(void)
	{
		return Stats::get_count(
			"SELECT COUNT(DISTINCT [Artist]) FROM [" +
			get_database()->usdx_scores + "];");
	}

	StatResultMostSungBand *StatResultMostSungBand::get_stats()
	{
		// TODO
		return NULL;
	}
}
