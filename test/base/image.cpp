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

#include "image.hpp"

#include <exception>
#include <cppunit/extensions/HelperMacros.h>
#include <log4cxx/logger.h>

#include <SDL/SDL.h>

namespace usdx
{
	class ImageTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(ImageTest);
		CPPUNIT_TEST(testBmp);
		CPPUNIT_TEST(testJpg);
		CPPUNIT_TEST(testGif);
		CPPUNIT_TEST(testPng);
		CPPUNIT_TEST_EXCEPTION(testNotAnImage, usdx::ImageLoadException);
 		CPPUNIT_TEST_SUITE_END();
	private:
		static log4cxx::LoggerPtr log;
	public:
		void setUp()
		{
		}

		void tearDown()
		{
		}

		void testBmp()
		{
			Image img(L"./testdata/test.bmp");
			const SDL_Surface *surface = img.get_surface();
			LOG4CXX_DEBUG(log, L"test.bmp: w = " << surface->w << L"; h = " << surface->h);
			CPPUNIT_ASSERT(40 == surface->w);
			CPPUNIT_ASSERT(30 == surface->h);
		}

		void testJpg()
		{
			Image img(L"./testdata/test.jpg");
			const SDL_Surface *surface = img.get_surface();
			LOG4CXX_DEBUG(log, L"test.jpg: w = " << surface->w << L"; h = " << surface->h);
			CPPUNIT_ASSERT(40 == surface->w);
			CPPUNIT_ASSERT(30 == surface->h);
		}

		void testPng()
		{
			Image img(L"./testdata/test.png");
			const SDL_Surface *surface = img.get_surface();
			LOG4CXX_DEBUG(log, L"test.png: w = " << surface->w << L"; h = " << surface->h);
			CPPUNIT_ASSERT(40 == surface->w);
			CPPUNIT_ASSERT(30 == surface->h);
		}

		void testGif()
		{
			Image img(L"./testdata/test.gif");
			const SDL_Surface *surface = img.get_surface();
			LOG4CXX_DEBUG(log, L"test.gif: w = " << surface->w << L"; h = " << surface->h);
			CPPUNIT_ASSERT(40 == surface->w);
			CPPUNIT_ASSERT(30 == surface->h);
		}

		void testNotAnImage()
		{
			Image img(L"./testdata/testsong_correct.txt");
			const SDL_Surface *surface = img.get_surface();
			LOG4CXX_DEBUG(log, L"testsong_correct.txt: w = " << surface->w << L"; h = " << surface->h);
		}
	};

	log4cxx::LoggerPtr ImageTest::log =
		log4cxx::Logger::getLogger("test.usdx.base.image");

	CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
};
