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

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "song.hpp"
#include "songloading/songloader.hpp"
#include <log4cxx/logger.h>

namespace usdx
{
	class SongloadingTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(SongloadingTest);
		CPPUNIT_TEST(testSongloadingTxtHeader);
		CPPUNIT_TEST_SUITE_END();

	private:
		int oldLogLevel;

	public:
		void setUp()
		{
			// save old loglevel in case we want to disable logging
			using namespace log4cxx;
			oldLogLevel = Logger::getRootLogger()->getEffectiveLevel()->toInt();
		}

		void tearDown()
		{
			// set old loglevel in case we did disable logging
			using namespace log4cxx;
			Logger::getRootLogger()->setLevel(Level::toLevel(oldLogLevel));
		}

		void testSongloadingTxtHeader()
		{
			Song *song = Songloader::get_instance()->load_header("testdata/testsong_correct.txt");
			
            CPPUNIT_ASSERT( "Test Ärtist" == song->get_artist() );
			CPPUNIT_ASSERT( "Test Title" == song->get_title() );
			CPPUNIT_ASSERT( "Test.mp3" == song->get_mp3() );
			CPPUNIT_ASSERT( 42.23f == song->get_bpm(0) );
            CPPUNIT_ASSERT( 42.23f == song->get_bpm(10) );
			CPPUNIT_ASSERT( 10 == song->get_gap() );
			CPPUNIT_ASSERT( "Test[BG].jpg" == song->get_background() );
			CPPUNIT_ASSERT( "Test[CO].jpg" == song->get_cover() );
			CPPUNIT_ASSERT( "Test Genre" == song->get_genre() );
			CPPUNIT_ASSERT( false == song->get_relative() );
			CPPUNIT_ASSERT( "Cpp" == song->get_language() );
			CPPUNIT_ASSERT( "Test[VD#12,3].mkv" == song->get_video() );
			CPPUNIT_ASSERT( 12.3f == song->get_video_gap() );
			CPPUNIT_ASSERT( 0 == song->get_start() );
			CPPUNIT_ASSERT( "Test0r" == song->get_creator() );
			CPPUNIT_ASSERT( 7 == song->get_year() );
			CPPUNIT_ASSERT( 666 == song->get_stop() );
			CPPUNIT_ASSERT( 0 == song->get_notes_gap() );
			// TODO
			//CPPUNIT_ASSERT( UTF-8 == song->get_encodeing() );

			delete song;
		}
	};

	CPPUNIT_TEST_SUITE_REGISTRATION(SongloadingTest);
};
