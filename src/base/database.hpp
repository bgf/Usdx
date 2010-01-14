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

#include <string>
#include <sqlite3.h>
#include <log4cxx/logger.h>

namespace usdx
{
	/**
	 * Abstract base class for all sqlite databases.
	 */
	class Database
	{
	private:
		static log4cxx::LoggerPtr log;

	protected:
		/**
		 * Internal reference to the sqlite database handle of the open
		 * sqlite database.
		 */
		sqlite3 *database;

		Database(std::string filename);
		virtual ~Database(void);

	public:
		/**
		 * Wrapper around the sqlite_prepare_v2 function with propper
		 * logging and exception throwing on error.
		 *
		 * @param sqlStatement SQL Statement for preparing to
		 * 	sqlite3_stmt
		 * @return Pointer to a sqlite3_stmt used for binding
		 * 	parameters and executing the statement. Need to be freed
		 * 	with sqlite3_finalize.
		 */
		sqlite3_stmt *sqlite_prepare(const std::string sqlStatement);

		/**
		 * Just a quick alias for sqlite_prepare, sqlite3_step and
		 * sqlite3_finalize.
		 */
		void sqlite_exec(const std::string sqlStatement);

		/**
		 * Check if the given table exists in the database.
		 *
		 * @param table Name to check if exists
		 * @return true, if table exists, false if not
		 */
		const bool sqlite_table_exists(const std::string table);

		/**
		 * Check if the given table has the given column by name.
		 *
		 * @param table Table to examine
		 * @param column Name of the column to check if exists
		 * @return true, if column exists in that table, false if not
		 */
		const bool sqlite_table_contains_column(const std::string table, const std::string column);

		/**
		 * Queries the user version from the sqlite database. This is a
		 * free settable additional field to identify the version of the
		 * schemata in the database.
		 *
		 * @see set_version(const int version)
		 * @return Value of the user_version setting of the sqlite
		 * 	database
		 */
		const int get_version(void);

		/**
		 * Set the user version of the database.
		 *
		 * @see get_version(void)
		 * @param version Current scheme version.
		 */
		void set_version(const int version);
	};
};

#endif
