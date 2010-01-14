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

#define STAT_DATABASE_TEST

#include "stats_database.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include <ctime>
#include <cstring>

namespace usdx
{
	class StatDatabaseTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(StatDatabaseTest);
/*		CPPUNIT_TEST(testNotNull);
		CPPUNIT_TEST(testGetVersion);
		CPPUNIT_TEST(testSetAndGetVersion);
		CPPUNIT_TEST(testSizeOfTime_t);
		CPPUNIT_TEST(testGetStatReset);
*/
		CPPUNIT_TEST(testFormatDate);
/*		CPPUNIT_TEST(testTableExists);
		CPPUNIT_TEST(testTableNotExists);
		CPPUNIT_TEST(testTableColumnExists);
		CPPUNIT_TEST(testTableColumnNotExists);
		CPPUNIT_TEST(testTableColumnTableNotExists);
*/
		CPPUNIT_TEST_SUITE_END();
	private:
		StatDatabase *db;
	public:
		void setUp()
		{
//			StatDatabase::init("../game/Ultrastar.db");
		}

		void tearDown()
		{
//			delete StatDatabase::get_instance();
		}

/*		void testNotNull()
		{
			CPPUNIT_ASSERT( NULL != StatDatabase::get_instance() );
		}

		void testGetVersion()
		{
			CPPUNIT_ASSERT( 1 == StatDatabase::get_instance()->get_version() );
		}

		void testSetAndGetVersion()
		{
			CPPUNIT_ASSERT( 1 == StatDatabase::get_instance()->get_version() );
			StatDatabase::get_instance()->set_version(0);
			CPPUNIT_ASSERT( 0 == StatDatabase::get_instance()->get_version() );
			StatDatabase::get_instance()->set_version(1);
			CPPUNIT_ASSERT( 1 == StatDatabase::get_instance()->get_version() );
		}

		void testSizeOfTime_t()
		{
			CPPUNIT_ASSERT( sizeof(time_t) == sizeof(long) );
		}

		void testGetStatReset()
		{
			CPPUNIT_ASSERT( 1000000000 < StatDatabase::get_instance()->get_stat_reset() );
		}
*/
		void testFormatDate()
		{
			char buf[9];
			StatDatabase::format_date(buf, 9, 1262433600);
			CPPUNIT_ASSERT( strcmp(buf, "13.02.09") );
		}
/*
		void testTableExists()
		{
			CPPUNIT_ASSERT( true == StatDatabase::get_instance()->sqlite_table_exists("us_songs") );
		}

		void testTableNotExists()
		{
			CPPUNIT_ASSERT( false == StatDatabase::get_instance()->sqlite_table_exists("abc") );
		}

		void testTableColumnExists()
		{
			CPPUNIT_ASSERT( true == StatDatabase::get_instance()->sqlite_table_contains_column("us_songs", "Title") );
		}

		void testTableColumnNotExists()
		{
			CPPUNIT_ASSERT( false == StatDatabase::get_instance()->sqlite_table_contains_column("us_songs", "title") );
		}

		void testTableColumnTableNotExists()
		{
			CPPUNIT_ASSERT( false == StatDatabase::get_instance()->sqlite_table_contains_column("abc", "Title") );
		}
*/	};

	CPPUNIT_TEST_SUITE_REGISTRATION(StatDatabaseTest);
};
