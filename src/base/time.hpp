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

#ifndef TIME_HPP
#define TIME_HPP

#include <stdint.h>

namespace usdx
{
	class Time
	{
	public:
		Time(void);
		float get_time();
	};


	class RelativeTimer
	{
	private:
		// system-clock reference time for calculation of CurrentTime
		uint64_t absolute_time;
		float relative_time_offset;
		bool paused;
		bool trigger_mode;

	public:
		RelativeTimer(bool trigger_mode = false);
		void pause(void);
		void resume(void);
		float get_time(void);
		float get_and_reset_time(void);
		void set_time(float time, bool trigger = true);
		void reset(void);
	};

};

#endif
