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
#include <cppunit/extensions/HelperMacros.h>

namespace usdx
{
	class StatDatabaseTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(StatDatabaseTest);
		CPPUNIT_TEST(testNotNull);
		CPPUNIT_TEST(testGetVersion);
		CPPUNIT_TEST(testSetAndGetVersion);
		CPPUNIT_TEST_SUITE_END();
	private:
		StatDatabase *db;
	public:
		void setUp()
		{
			StatDatabase::init("../game/Ultrastar.db");
		}

		void tearDown()
		{
			delete StatDatabase::get_instance();
		}

		void testNotNull()
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
	};

	CPPUNIT_TEST_SUITE_REGISTRATION(StatDatabaseTest);
};
