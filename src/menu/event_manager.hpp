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

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL/SDL.h>

#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/progress.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/signals2.hpp>

#include <log4cxx/logger.h>

namespace usdx
{
	/**
	 * This class is the junction point between the SDL Thread (with the SDL
	 * main loop) and the event thread. The EventManager buffers the SDL
	 * Events until the thread has time to handle the events. Because one
	 * thread pushes the events and an other thread is reading the access to
	 * the buffer have to be mutual exclusive.
	 */
	class EventManager
	{
	private:
		static log4cxx::LoggerPtr log;

		EventManager(const EventManager&);		//< no copy
		EventManager& operator=(const EventManager&);	//< no assignment

		/**
		 * Type of the buffer for the Events.
		 */
		typedef boost::circular_buffer<const SDL_Event*> buffer_type;

		/**
		 * Buffer to store the events.
		 */
		buffer_type buffer;

		/**
		 * How many events currently waiting to getting handled.
		 */
		buffer_type::size_type waiting;

		/**
		 * Mutex to guaranty the mutual exclusion between the multiple
		 * threads.
		 */
		boost::mutex mutex;

		boost::condition not_empty;
		boost::condition not_full;

		/**
		 * Returns if the buffer is contains at least one element or
		 * not.
		 * This functions is not thread-safe! Intended to use as
		 * condition for boost::condition#wait.
		 */
		bool is_not_empty() const;

		/**
		 * Returns if the buffer has at least space for one element left
		 * or not.
		 * This functions is not thread-safe! Intended to use as
		 * condition for boost::condition#wait.
		 */
		bool is_not_full() const;

		/**
		 * This function is used to get the next event from the
		 * buffer. If no event is waiting, this method blocks until
		 * there is one event available.
		 */
		void get_next_event(SDL_Event& event);

	public:
		EventManager(int capacity = 20);
		virtual ~EventManager();

		void add_event(const SDL_Event& item);

		/**
		 * This function is intended to be used as separate thread. It
		 * will run forever until for example a
		 * boost::thread_interrupted is thrown.
		 */
		void handle_events(void);

		/**
		 * This function returns (thread-safe) weather there is space in
		 * left the buffer for a new element or not.
		 */
		bool available(void);


		boost::signals2::signal<void (int, int)> mouse_move;
	};
};


#endif
