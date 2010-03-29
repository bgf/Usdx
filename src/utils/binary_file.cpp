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

#include "binary_file.hpp"
#include <string>

namespace usdx
{
	BinaryFile::BinaryFile(const std::string& filename) : file(filename.c_str(), std::ifstream::in | std::ifstream::binary), content(NULL)
	{
	}

	BinaryFile::BinaryFile(const boost::filesystem::wpath& path) : file(path, std::ifstream::in | std::ifstream::binary), content(NULL)
	{
	}

	BinaryFile::~BinaryFile(void)
	{
		if (content) {
			delete[] content;
			content = NULL;
		}

		file.close();
	}

	std::istream &BinaryFile::stream(void)
	{
		return file;
	}

	const std::streamsize BinaryFile::get_filesize(void)
	{
		std::streampos position = stream().tellg();

		stream().seekg (0, std::ios::end);
		std::streamsize length = stream().tellg();
		stream().seekg (position);

		return length;
	}

	const void* BinaryFile::get_content(void)
	{
		if (content == NULL) {
			std::streamsize length = get_filesize();

			content = new char[length];
			stream().read(content, length);
		}

		return (void*)content;
	}
};
