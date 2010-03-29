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
	}

	Songloader::~Songloader(void)
	{
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

	Song *Songloader::load_header(const boost::filesystem::wpath& filename)
	{
		std::wstring ext = extension(filename);
		std::map<std::wstring, SongloadingStrategyBaseFactory*>::iterator it = strategies.find(ext);
		if (it == strategies.end()) {
			LOG4CXX_WARN(log, L"No SongloadingStrategy found for file extension: '" << ext << L"'");
			throw NoStrategyException("Unknown file format.");
		}

		return it->second->get_songloader()->load_header(filename);
	}

	Song* Songloader::load_song(Song* song)
	{
		std::wstring ext = extension(song->get_filename());
		std::map<std::wstring, SongloadingStrategyBaseFactory*>::iterator it = strategies.find(ext);
		if (it == strategies.end()) {
			LOG4CXX_WARN(log, L"No SongloadingStrategy found for file extension: '" << ext << L"'");
			throw NoStrategyException("Unknown file format.");
		}

		return it->second->get_songloader()->load_song(song);
	}

	void Songloader::add_strategy(SongloadingStrategyBaseFactory *factory)
	{
		if (factory) {
			strategies[factory->get_fileextension()] = factory;
		}
	}
};
