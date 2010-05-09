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

#include <image.hpp>
#include <SDL/SDL_image.h>
#include "utils/binary_file.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Image::log =
		log4cxx::Logger::getLogger("usdx.base.Image");

	ImageLoadException::ImageLoadException(std::string error) :
		error(error)
	{
	}

	ImageLoadException::~ImageLoadException() throw()
	{
	}

	const char* ImageLoadException::what() const throw()
	{
		return error.c_str();
	}

	Image::Image(boost::filesystem::wpath filename) :
		filename(filename), surface(NULL)
	{
	}

	Image::~Image()
	{
		if (surface != NULL) {
			SDL_FreeSurface(surface);
			surface = NULL;
		}
	}

	void Image::load(void)
	{
		BinaryFile file(filename);

		SDL_RWops* source = SDL_RWFromConstMem(file.get_content(), file.get_filesize());
		surface = IMG_Load_RW(source, 1);

		if (surface == NULL) {
			LOG4CXX_ERROR(log, L"Error loading image: " << filename);
			throw ImageLoadException(IMG_GetError());
		}
	}

	SDL_Surface* Image::get_surface(void)
	{
		if (surface == NULL) {
			load();
		}

		return surface;
	}
};
