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

#include "time.hpp"
#include <SDL/SDL.h>

#define SDL_CORRECTION_RATIO 1000

namespace usdx
{

	Time::Time(void)
	{
	}

	float Time::get_time()
	{
		return SDL_GetTicks() / SDL_CORRECTION_RATIO;
	}


	/*
	 * RelativeTimer
	 */

	/*
	 * creates a new timer.
	 * if triggermode is false (default), the timer
	 * will immediately begin with counting.
	 * if triggermode is true, it will wait until get/settime() or pause() is called
	 * for the first time.
	 */
	RelativeTimer::RelativeTimer(bool trigger_mode)
	{
		this->trigger_mode = trigger_mode;
		reset();
		this->paused = false;
	}

	void RelativeTimer::pause(void)
	{
		relative_time_offset = get_time();
		paused = true;
	}

	void RelativeTimer::resume(void)
	{
		absolute_time = SDL_GetTicks();
		paused = false;
	}

	/*
	 * Returns the counter of the timer.
	 * If in TriggerMode it will return 0 and start the counter on the first call.
	 */
	float RelativeTimer::get_time(void)
	{
		// initialize absolute time on first call in triggered mode
		if (trigger_mode && (absolute_time == 0))
		{
			absolute_time = SDL_GetTicks();
			return relative_time_offset;
		}

		if (paused)
			return relative_time_offset;

		return relative_time_offset + (SDL_GetTicks() - absolute_time) / SDL_CORRECTION_RATIO;
	}

	/*
	 * Returns the counter of the timer and resets the counter to 0 afterwards.
	 * Note: In TriggerMode the counter will not be stopped as with Reset().
	 */
	float RelativeTimer::get_and_reset_time(void)
	{
		float result = get_time();
		set_time(0);
		return result;
	}

	/*
	 * Sets the timer to the given time. This will trigger in TriggerMode if
	 * Trigger is set to true. Otherwise the counter's state will not change.
	 */
	void RelativeTimer::set_time(float time, bool trigger)
	{
		relative_time_offset = time;

		if (!trigger_mode || trigger)
			absolute_time = SDL_GetTicks();
	}

	/*
	 * Resets the counter of the timer to 0.
	 * If in TriggerMode the timer will not start counting until it is triggered again.
	 */
	void RelativeTimer::reset(void)
	{
		relative_time_offset = 0;

		if (trigger_mode)
			absolute_time = 0;
		else
			absolute_time = SDL_GetTicks();
	}
}
