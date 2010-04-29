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

#include "event_manager.hpp"
#include <iostream>

namespace usdx
{
	log4cxx::LoggerPtr EventManager::log =
		log4cxx::Logger::getLogger("usdx.menu.event_manager");

	EventManager::EventManager(int capacity) :
		buffer(capacity), waiting(0)
	{
	}

	EventManager::~EventManager(void)
	{
	}

	bool EventManager::is_not_full() const
	{
		return waiting < buffer.capacity();
	}

	bool EventManager::is_not_empty() const
	{
		return waiting > 0;
	}

	void EventManager::add_event(const SDL_Event& event)
	{
		boost::mutex::scoped_lock lock(mutex);

		not_full.wait(lock, boost::bind(&EventManager::is_not_full, this));

		buffer.push_front(new SDL_Event(event));
		++waiting;

		lock.unlock();
		not_empty.notify_one();
	}

	void EventManager::get_next_event(SDL_Event& event)
	{
		boost::mutex::scoped_lock lock(mutex);

		not_empty.wait(lock, boost::bind(&EventManager::is_not_empty, this));

		--waiting;
		event = *buffer[waiting];
		delete buffer[waiting];

		lock.unlock();
		not_full.notify_one();
	}

	bool EventManager::available(void)
	{
		boost::mutex::scoped_lock lock(mutex);
		return waiting < buffer.capacity();
	}

	void EventManager::handle_events(void)
	{
		SDL_Event event;

		// run forever until this thread is interrupted
		while (true) {
			get_next_event(event);

			switch (event.type) {
			case SDL_KEYDOWN:
				LOG4CXX_ERROR(log, L"key");
				break;

			case SDL_MOUSEMOTION:
				mouse_move(event.motion.x, event.motion.y);
			}
		}
	}
};

