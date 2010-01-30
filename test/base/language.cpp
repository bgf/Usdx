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

#include "language.hpp"

#include <exception>
#include <cppunit/extensions/HelperMacros.h>
#include <log4cxx/logger.h>

namespace usdx
{
	class LanguageTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(LanguageTest);
		CPPUNIT_TEST(testInit);
		CPPUNIT_TEST_EXCEPTION(testLangDirIsFile, std::invalid_argument);
		CPPUNIT_TEST_EXCEPTION(testLangDirNotExists, std::invalid_argument);
		CPPUNIT_TEST(testNoInit);
		CPPUNIT_TEST_SUITE_END();
	private:
		static log4cxx::LoggerPtr log;
	public:
		void setUp()
		{
		}

		void tearDown()
		{
			delete Language::get_instance();
		}

		void testInit()
		{
			Language::get_instance()->init(L"../game/languages/");
			LOG4CXX_DEBUG(log, L" -" << _(L"SING_SONG_SELECTION_DESC") << "-");
			CPPUNIT_ASSERT(_(L"SING_SONG_SELECTION_DESC") == L"choose your song");

			Language::get_instance()->set_language(L"German");
			LOG4CXX_DEBUG(log, L" -" << _(L"SING_SONG_SELECTION_DESC") << "-");
			CPPUNIT_ASSERT(_(L"SING_SONG_SELECTION_DESC") == L"Wähle deinen Song");
		}

		void testLangDirIsFile()
		{
			Language::get_instance()->init(L"../game/languages/English.ini");
		}

		void testLangDirNotExists()
		{
			Language::get_instance()->init(L"../foo/blub/");
		}

		void testNoInit()
		{
			LOG4CXX_DEBUG(log, L" -" << _(L"SING_SONG_SELECTION_DESC") << "-");
			CPPUNIT_ASSERT(_(L"SING_SONG_SELECTION_DESC") == L"SING_SONG_SELECTION_DESC");
		}
	};

	log4cxx::LoggerPtr LanguageTest::log =
		log4cxx::Logger::getLogger("test.usdx.base.language");

	CPPUNIT_TEST_SUITE_REGISTRATION(LanguageTest);
};
