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

#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <map>
#include <string>
#include <boost/filesystem.hpp>
#include <log4cxx/logger.h>
#include "utils/base_exception.hpp"

/**
 * Helper macro for translating strings with a short pseudo function call.
 */
#define _(x) Language::get_instance()->translate(x)

namespace usdx
{
	class LanguageNotFound : public BaseException
	{
	private:
		std::wstring language;
	public:
		LanguageNotFound(const std::wstring& language);
		~LanguageNotFound () throw () {};

		const std::wstring& get_language() const;
	};

	class Language
	{
	private:
		static log4cxx::LoggerPtr log;

		boost::filesystem::wpath language_dir;

		std::map<std::wstring, std::wstring>* current_translation;
		std::wstring current_language;

		std::map<std::wstring, std::wstring>* default_translation;

		std::map<std::wstring, std::map<std::wstring, std::wstring>*> translations;

		void parse_translation(const std::wstring& line,
				       std::map<std::wstring, std::wstring>& map);

		void load_language(const std::wstring& language);
		void load_default_language(const std::wstring& language);

		Language();

		static Language* instance;
	public:
		virtual ~Language();

		static Language* get_instance();

		void init(const boost::filesystem::wpath& language_dir,
			  const std::wstring& default_language = L"English");

		void set_language(const std::wstring& language);
		const std::wstring& get_language(void) const;

		const std::wstring& translate(const std::wstring& source) const;
	};
};

#endif
