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

#include <boost/filesystem.hpp>
#include "language.hpp"

// namespace alias for shorter class names
namespace fs = boost::filesystem;

namespace usdx
{
	Language* Language::instance = NULL;

	LanguageNotFound::LanguageNotFound(const std::wstring& language) :
		BaseException("Language not found!"),
		language(language)
	{
	}

	const std::wstring& LanguageNotFound::get_language() const
	{
		return language;
	}


	Language::Language(void)
	{
	}

	Language::~Language(void)
	{

		// remove reference from singleton to make regeneration possible
		instance = NULL;
	}

	Language* Language::get_instance(void)
	{
		if (instance == NULL) {
			instance = new Language();
		}

		return instance;
	}

	void Language::load_language(const std::wstring& language)
	{
		// TODO
	}

	void Language::init(const fs::wpath& language_dir)
	{
		if (!is_directory(language_dir)) {
			return;
		}

		this->language_dir = language_dir;

		// default construction yields past-the-end
		fs::wdirectory_iterator end_it;
		for (fs::wdirectory_iterator it(language_dir); it != end_it; ++it)
		{
			if (!is_directory(it->status()))
			{
				if (extension(it->path()) == L".ini")
				{
					translations[basename(it->path())] = NULL;
				}
			}
		}
	}

	void Language::set_language(const std::wstring& language)
	{
		std::map<std::wstring, std::map<std::wstring, std::wstring>*>::iterator it = translations.find(language);
		if (it == translations.end()) {
			throw LanguageNotFound(language);
		}

		if (it->second == NULL) {
			load_language(language);
		}

		current_language_name = std::wstring(language);
		current_language = translations[current_language_name];
	}

	const std::wstring& Language::get_language(void) const
	{
		return current_language_name;
	}

	const std::wstring& Language::translate(const std::wstring& source) const
	{

		std::map<std::wstring, std::wstring>::iterator it = current_language->find(source);
		if (it != current_language->end()) {
			return it->second;
		}

		it = default_language->find(source);
		if (it != default_language->end()) {
			return it->second;
		}

		return source;
	}
};
