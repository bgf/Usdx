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

#include "ringbuffer.hpp"
#include <cstring>
#include <cppunit/extensions/HelperMacros.h>

namespace usdx
{
	class RingBufferTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(RingBufferTest);
		CPPUNIT_TEST(testReadNullBuffer);
		CPPUNIT_TEST(testReadNegativeCount);
		CPPUNIT_TEST(testReadEmptyRingBuffer);
		CPPUNIT_TEST(testWriteNullBuffer);
		CPPUNIT_TEST(testWriteNegativeCount);
		CPPUNIT_TEST(testWriteOverflow);
		CPPUNIT_TEST(testWriteOverflow2);
		CPPUNIT_TEST(testWriteRead);
		CPPUNIT_TEST(testReadMoreThanAvailable);
		CPPUNIT_TEST(testCurrentSize);
		CPPUNIT_TEST(testCurrentAvailable);
		CPPUNIT_TEST(testFlush);
		CPPUNIT_TEST_SUITE_END();
	private:
		RingBuffer *rbuff;
	public:
		void setUp()
		{
			rbuff = new RingBuffer(10);
		
		}

		void tearDown()
		{
			delete rbuff;
		}

		// check if the read function reports an error in form of a 
		// negative value when the given buffer is NULL
		void testReadNullBuffer()
		{
			CPPUNIT_ASSERT( -1 == rbuff->read(NULL,10) );
		}

		// check if the read function reports an error in form of a
		// negative value when the given count is negative
		void testReadNegativeCount()
		{
			char buffer[10];
			CPPUNIT_ASSERT( -1 == rbuff->read(buffer,-1) );
		}

		// check the returnvalue when reading on a empty ringbuffer
		void testReadEmptyRingBuffer()
		{
			char buffer[10];
			CPPUNIT_ASSERT( 0 == rbuff->read(buffer,10) );
		}

		// check in the read function reports an error in form of a 
		// negative value when the given buffer is NULL
		void testWriteNullBuffer()
		{
			CPPUNIT_ASSERT( -1 == rbuff->write(NULL,10) );
		}

		// check if the read function reports an error in form of a
		// negative value when the given count is negative
		void testWriteNegativeCount()
		{
			char buffer[10];
			CPPUNIT_ASSERT( -1 == rbuff->write(buffer,-1) );
		}

		// checks the retrunvalue when writeing over the limits of a
		// ringbuffer
		void testWriteOverflow()
		{
			char buffer[20];
			CPPUNIT_ASSERT( 0 == rbuff->read(buffer,20) );
		}

		// check if the read value is ajusted correctly, when
		// a buffer overflow happens
		void testWriteOverflow2()
		{
			char w1Buffer[4]="AAA";
			char w2Buffer[4]="BBB";
			char rBuffer[7]="CCCCCC";
			CPPUNIT_ASSERT( 3 == rbuff->write(w1Buffer,3) );
			CPPUNIT_ASSERT( 3 == rbuff->write(w1Buffer,3) );
			CPPUNIT_ASSERT( 3 == rbuff->write(w1Buffer,3) );
			CPPUNIT_ASSERT( 4 == rbuff->write(w2Buffer,4) );
			CPPUNIT_ASSERT( 6 == rbuff->read(rBuffer,6) );
			CPPUNIT_ASSERT( 0 == strcmp("AAAAAA",rBuffer) );
		}

		// check if inputdata equals outputdata
		void testWriteRead()
		{
			char w1Buffer[4]="AAA";
			char w2Buffer[4]="BBB";
			char rBuffer[7]="CCCCCC";
			CPPUNIT_ASSERT( 3 == rbuff->write(w1Buffer,3) );
			CPPUNIT_ASSERT( 4 == rbuff->write(w2Buffer,4) );
			CPPUNIT_ASSERT( 7 == rbuff->read(rBuffer,7) );
			CPPUNIT_ASSERT( 0 == strcmp("AAABBB",rBuffer) );
		}

		// check what happens when read trys to read more data than
		// available
		void testReadMoreThanAvailable()
		{
			char wBuffer[4]="AAA";
			char rBuffer[5]="BBBB";
			CPPUNIT_ASSERT( 4 == rbuff->write(wBuffer,4) );
			CPPUNIT_ASSERT( 4 == rbuff->read(rBuffer,5) );
			CPPUNIT_ASSERT( 0 == strcmp("AAA",rBuffer) );
		}

		// check if the correct ringbuffer size is reported
		void testCurrentSize()
		{
			char w1Buffer[4]="AAA";
			char w2Buffer[5]="BBBB";
			CPPUNIT_ASSERT( 4 == rbuff->write(w1Buffer,4) );
			CPPUNIT_ASSERT( 5 == rbuff->write(w2Buffer,5) );
			CPPUNIT_ASSERT( 10 == rbuff->get_size() );
		}

		// check if the available space in the ringbuffer
		void testCurrentAvailable()
		{
			char w1Buffer[4]="AAA";
			char w2Buffer[5]="BBBB";
			CPPUNIT_ASSERT( 4 == rbuff->write(w1Buffer,4) );
			CPPUNIT_ASSERT( 5 == rbuff->write(w2Buffer,5) );
			CPPUNIT_ASSERT( 9 == rbuff->get_available() );
		}
		
		// check if the flush function clears the buffer correctly
		void testFlush()
		{
			char w1Buffer[4]="AAA";
			char w2Buffer[4]="BBB";
			char rBuffer[4]="CCC";
			CPPUNIT_ASSERT( 4 == rbuff->write(w1Buffer,4) );
			rbuff->flush();
			CPPUNIT_ASSERT( 4 == rbuff->write(w2Buffer,4) );
			CPPUNIT_ASSERT( 4 == rbuff->read(rBuffer,4) );
			CPPUNIT_ASSERT( 0 == strcmp("BBB",rBuffer) );
		}

	};

	CPPUNIT_TEST_SUITE_REGISTRATION(RingBufferTest);
};
