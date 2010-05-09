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

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <boost/filesystem.hpp>
#include <GL/gl.h>

#include "utils/point_3d.hpp"
#include "utils/dimension.hpp"
#include "utils/rectangle.hpp"
#include "image.hpp"
#include "drawable.hpp"

namespace usdx
{
	class TextureLoadException
	{
	public:
		TextureLoadException() {};
		virtual ~TextureLoadException() {};
	};

	class TextureSizeException : public TextureLoadException
	{
	private:
		Dimension size;

	public:
		TextureSizeException(Dimension size) : size(size) { };
		virtual ~TextureSizeException() { };
	};

	class TextureColorDepthException : public TextureLoadException
	{
	private:
		unsigned int number_of_colors;

	public:
		TextureColorDepthException(unsigned int number_of_colors) : number_of_colors(number_of_colors) {};
		virtual ~TextureColorDepthException() {};
	};

	class Texture
	{
	private:
		static log4cxx::LoggerPtr log;

		boost::filesystem::wpath filename;

		GLuint texture;
		GLenum texture_format;

		Dimension size;

		float rotation; ///< radiant (0 - 2*pi)

	public:
		Texture(boost::filesystem::wpath filename);
		virtual ~Texture();

		GLuint get_texture(void) const;
	};
};

#endif
