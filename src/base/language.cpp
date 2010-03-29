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

#include <exception>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "language.hpp"
#include "utils/unicode_file.hpp"

// namespace alias for shorter class names
namespace fs = boost::filesystem;

namespace usdx
{
	Language* Language::instance = NULL;

	log4cxx::LoggerPtr Language::log =
		log4cxx::Logger::getLogger("usdx.base.language");

	LanguageNotFound::LanguageNotFound(const std::wstring& language) :
		BaseException("Language not found!"),
		language(language)
	{
	}

	const std::wstring& LanguageNotFound::get_language() const
	{
		return language;
	}


	Language::Language(void) : current_translation(NULL), default_translation(NULL)
	{
	}

	void remove_element(std::pair<std::wstring, std::map<std::wstring, std::wstring>*> element)
	{
		if (element.second) {
			element.second->clear();
		}

		delete element.second;
		element.second = NULL;
	}

	Language::~Language(void)
	{
		// clear memory for all elements in the map
		std::for_each(translations.begin(), translations.end(),
			      remove_element);
		translations.clear();

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

	void Language::parse_translation(const std::wstring& line, std::map<std::wstring, std::wstring>& map)
	{
		size_t found = line.find(L"=");
		if (found != std::wstring::npos) {
			// copy the substring until '=' and
			// transform to upper case
			std:: wstring key(found, L' ');
			std::transform(line.begin(), line.begin() + found,
				       key.begin(), toupper);
			boost::trim(key);

			std::wstring value(line.substr(found + 1));
			boost::trim_if(value, boost::is_cntrl());
			boost::trim(value);

			LOG4CXX_TRACE(log, L"Found translation from " <<
				      key << L" to " << value);

			map[key] = value;
		}
	}

	void Language::load_language(const std::wstring& language)
	{
		fs::wpath source_path = language_dir / (language + L".ini");

		if (exists(source_path)) {
			std::map<std::wstring, std::wstring> *map =
				new std::map<std::wstring, std::wstring>();

			UnicodeFile source(source_path);

			bool started = false;
			std::wstring line;

			while (source.stream().good()) {
				getline(source.stream(), line);

				if (started) {
					if (line[0] == L'[' && line[line.length() - 1] == L']') {
						break;
					}

					parse_translation(line, *map);
				}
				else {
					if (line.compare(L"[Text]")) {
						started = true;
					}
				}
			}

			translations[basename(source_path)] = map;
		}
	}

	void Language::load_default_language(const std::wstring& default_language)
	{
		std::map<std::wstring, std::map<std::wstring, std::wstring>*>::iterator it = translations.find(default_language);
		if (it != translations.end()) {
			LOG4CXX_DEBUG(log, L"Loading default language: " << default_language);
			load_language(default_language);
			current_translation = default_translation = translations[default_language];
			current_language = default_language;
		}
	}

	void Language::init(const fs::wpath& language_dir, const std::wstring& default_language)
	{
		if (!is_directory(language_dir)) {
			throw std::invalid_argument("language_dir should be a directory");
		}

		this->language_dir = language_dir;

		// default construction yields past-the-end
		fs::wdirectory_iterator end_it;
		for (fs::wdirectory_iterator it(language_dir); it != end_it; ++it)
		{
			if (!is_directory(it->status()) &&
			    extension(it->path()) == L".ini")
			{
				translations[basename(it->path())] = NULL;
			}
		}

		load_default_language(default_language);
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

		current_language = std::wstring(language);
		current_translation = translations[current_language];
	}

	const std::wstring& Language::get_language(void) const
	{
		return current_language;
	}

	const std::wstring& Language::translate(const std::wstring& source) const
	{
		if (current_translation) {
			std::map<std::wstring, std::wstring>::iterator it = current_translation->find(source);
			if (it != current_translation->end()) {
				return it->second;
			}
		}

		if (default_translation) {
			std::map<std::wstring, std::wstring>::iterator it = default_translation->find(source);
			if (it != default_translation->end()) {
				return it->second;
			}
		}


		return source;
	}
};
