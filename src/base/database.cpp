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
	log4cxx::LoggerPtr Database::log = log4cxx::Logger::getLogger("usdx.base.Database");

	Database::Database(const std::string filename)
	{
		if (SQLITE_OK != sqlite3_open_v2(filename.c_str(), &this->database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
			sqlite3_close(database);
			throw "Error opening database.";
		}
	}

	Database::~Database(void)
	{
		/* frees database */
		LOG4CXX_DEBUG(log, "Closing Database");

		sqlite3_close(database);
		database = NULL;
	}

	sqlite3_stmt *Database::sqlite_prepare(const std::string sqlStatement)
	{
		sqlite3_stmt *sqliteStatement;
		if (SQLITE_OK != sqlite3_prepare_v2(database, sqlStatement.c_str(), sqlStatement.length(), &sqliteStatement, NULL)) {
			sqlite3_finalize(sqliteStatement);

			LOG4CXX_ERROR(log, "Error '" << sqlite3_errmsg(database) << "' in SQL '" << sqlStatement << "'");
			throw "Error preparing statement.";
		}

		return sqliteStatement;
	}

	void Database::sqlite_exec(const std::string sqlStatement)
	{
		sqlite3_stmt *sqliteStatement = sqlite_prepare(sqlStatement);
		sqlite3_step(sqliteStatement);
		sqlite3_finalize(sqliteStatement);
	}

	const bool Database::sqlite_table_exists(const std::string table)
	{
		std::string sql = "select [name] from [sqlite_master] where [type] = 'table' and [tbl_name] = ?1;";
		sqlite3_stmt *sqliteStatement = sqlite_prepare(sql);

		// bind table name to parameter 1 and execute statement
		sqlite3_bind_text(sqliteStatement, 1, table.c_str(), table.length(), SQLITE_TRANSIENT);
		int rc = sqlite3_step(sqliteStatement);

		// if rc is SQLITE_ROW, than result has at lease one row and so
		// the table exists
		bool result = false;
		if (rc == SQLITE_ROW) {
			result = true;
		}

		sqlite3_finalize(sqliteStatement);
		return result;
	}

	const bool Database::sqlite_table_contains_column(const std::string table, const std::string column)
	{
		sqlite3_stmt *sqliteStatement = sqlite_prepare("PRAGMA TABLE_INFO([" + table + "]);");
		bool result = false;

		int rc = sqlite3_step(sqliteStatement);
		while (rc == SQLITE_ROW) {
			const char *column_name = (const char*)sqlite3_column_blob(sqliteStatement, 1);

			if (column == std::string(column_name)) {
				result = true;
				break;
			}

			rc = sqlite3_step(sqliteStatement);
		}

		sqlite3_finalize(sqliteStatement);
		return result;
	}

	const int Database::get_version(void)
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

	void Database::set_version(const int version)
	{
		// format the PRAGMA statement (PRAGMA does _not_ support parameters)
		std::ostringstream sqlStatementBuffer (std::ostringstream::out);
		sqlStatementBuffer << "PRAGMA user_version = " << version << ";";

		sqlite_exec(sqlStatementBuffer.str());
	}
};
