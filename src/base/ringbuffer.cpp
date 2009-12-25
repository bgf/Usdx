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
#include <stdlib.h>
#include <string.h>

namespace usdx
{

	RingBuffer::RingBuffer(int size)
	{
		buffer_size = size;

		ring_buffer = (char*)malloc(size);
		if (ring_buffer == NULL)
			throw "No memory";
	}

	RingBuffer::~RingBuffer()
	{
		free(ring_buffer);
	}

	int RingBuffer::read(char *buffer, int count)
	{
		// check if there is something to do
		if (count <= 0)
			return count;

		// adjust output count
		if (count > buffer_count)
		{
			//DebugWriteln('Read too much: ' + inttostr(count) +',count:'+ inttostr(BufferCount) + '/size:' + inttostr(BufferSize));
			count = buffer_count;
		}

		// copy data to output buffer

		// first step: copy from the area between the read-position and the end of the buffer
		int part_count = (count < buffer_size - read_pos) ? count : (buffer_size - read_pos);
		memcpy(buffer, ring_buffer + read_pos, part_count);

		// second step: if we need more data, copy from the beginning of the buffer
		if (part_count < count)
			memcpy(buffer + part_count, ring_buffer, count - part_count);

		// mark the copied part of the buffer as free
		buffer_count = buffer_count - count;
		read_pos = (read_pos + count) % buffer_size;

		return count;
	}

	int RingBuffer::write(char *buffer, int count)
	{
		// check for a reasonable request
		if (count <= 0)
			return count;

		// skip input data if the input buffer is bigger than the ring-buffer
		if (count > buffer_size)
		{
			//DebugWriteln('Write skip data:' + inttostr(count) +',count:'+ inttostr(BufferCount) + '/size:' + inttostr(BufferSize));
			buffer += count - buffer_size;
			count = buffer_size;
		}

		// first step: copy to the area between the write-position and the end of the buffer
		int part_count = (count < buffer_size - write_pos) ? count : (buffer_size - write_pos);
		memcpy(ring_buffer + write_pos, buffer, part_count);

		// second step: copy data to front of buffer
		if (part_count < count)
			memcpy(ring_buffer, buffer + part_count, count - part_count);

		// update info
		buffer_count = (buffer_count + count < buffer_size) ? (buffer_count + count) : buffer_size;
		write_pos = (write_pos + count) % buffer_size;

		// if the buffer is full, we have to reposition the read-position
		if (buffer_count == buffer_size)
			read_pos = write_pos;

		return count;
	}

	int RingBuffer::get_available()
	{
		return buffer_count;
	}

	int RingBuffer::get_size()
	{
		return buffer_size;
	}

	void RingBuffer::flush()
	{
		read_pos = 0;
		write_pos = 0;
		buffer_count = 0;
	}
};
