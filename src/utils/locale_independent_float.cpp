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

#include "locale_independent_float.hpp"
#include <iostream>
#include <sstream>

namespace usdx
{
	LocaleIndependentFloat::LocaleIndependentFloat()
	{
	}

	LocaleIndependentFloat::~LocaleIndependentFloat()
	{
	}

	const float LocaleIndependentFloat::get_value()
	{
		return this->value;
	}

	void LocaleIndependentFloat::set_value(const float value)
	{
		this->value = value;
	}

	LocaleIndependentFloat& LocaleIndependentFloat::operator= (const LocaleIndependentFloat& value)
	{
		this->value = value.value;
		return *this;
	}

	LocaleIndependentFloat& LocaleIndependentFloat::operator= (const float& vaule)
	{
		this->value = value;
		return *this;
	}

	std::istream& operator>> (std::istream& is, LocaleIndependentFloat& float_value)
	{
		return is >> &float_value;
	}

	std::istream& operator>> (std::istream& is, LocaleIndependentFloat* float_value)
	{
		std::string str_value;
		is >> str_value;

		std::size_t found = str_value.find(',');
		if (found != std::string::npos) {
			str_value[found] = '.';
		}

		std::istringstream str(str_value);
		float value;
		str >> value;

		float_value->set_value(value);

		return is;
	}
};
