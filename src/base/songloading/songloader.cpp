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

#include "songloader.hpp"
#include "songloading_strategy_txt.hpp"
#include "songloading_strategy_xml.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Songloader::log =
		log4cxx::Logger::getLogger("usdx.base.songloading.Songloader");

	Songloader *Songloader::instance = NULL;

	Songloader::Songloader(void)
	{
		// add different strategies to map
		strategies[".txt"] = new SongloadingStrategyTxt();
		strategies[".xml"] = new SongloadingStrategyXml();
	}

	void remove_element(std::pair<std::string, SongloadingStrategy*> e)
	{
		delete e.second;
		e.second = NULL;
	}

	Songloader::~Songloader(void)
	{
		// clear memory for all elements in the map
		std::for_each(strategies.begin(), strategies.end(),
			      remove_element);
		strategies.clear();

		// remove reference from singleton to make regeneration possible
		instance = NULL;
	}

	Songloader *Songloader::get_instance(void)
	{
		if (instance == NULL) {
			instance = new Songloader();
		}

		return instance;
	}

	Song *Songloader::load_header(std::string filename)
	{
		std::string extension = "";

		size_t found = filename.rfind('.');
		if (found != std::string::npos) {
			extension = filename.substr(found);
		}

		std::map<std::string, SongloadingStrategy*>::iterator it = strategies.find(extension);
		if (it == strategies.end()) {
			LOG4CXX_WARN(log, "No SongloadingStrategy found for file extension: '" << extension << "'");
			throw NoStrategyException("Unknown file format.");
		}

		return it->second->load_header(filename);
	}

	Song* Songloader::load_song(Song* song)
	{
		std::string extension = "";

		size_t found = song->get_filename().rfind('.');
		if (found != std::string::npos) {
			extension = song->get_filename().substr(found);
		}

		std::map<std::string, SongloadingStrategy*>::iterator it = strategies.find(extension);
		if (it == strategies.end()) {
			LOG4CXX_WARN(log, "No SongloadingStrategy found for file extension: '" << extension << "'");
			throw NoStrategyException("Unknown file format.");
		}

		return it->second->load_song(song);
	}
};
