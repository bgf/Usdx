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

#include "texture.hpp"

namespace usdx
{
	log4cxx::LoggerPtr Texture::log =
		log4cxx::Logger::getLogger("usdx.base.texture");

	Texture::Texture(boost::filesystem::wpath filename) :
		filename(filename), texture(0), size(0, 0), rotation(0)
	{
		Image image(filename);

		size.set_width(image.get_surface()->w);
		size.set_height(image.get_surface()->h);

		// // Check that the image dimensions are a power of 2
		// if ((image.get_surface()->w & (image.get_surface()->w - 1)) != 0 ) {
		// 	LOG4CXX_ERROR(log, L"" << filename << L" has a width of " << image.get_surface()->w << L" that is not a power of 2");
		// 	throw TextureSizeException(size);
		// }

		// if ((image.get_surface()->h & (image.get_surface()->h - 1)) != 0 ) {
		// 	LOG4CXX_ERROR(log, L"" << filename << L" has a height of " << image.get_surface()->h << L" that is not a power of 2");
		// 	throw TextureSizeException(size);
		// }


		switch (image.get_surface()->format->BytesPerPixel) {
		case 4:
			if (image.get_surface()->format->Rmask == 0x000000ff) {
				texture_format = GL_RGBA;
			}
			else {
				texture_format = GL_BGRA;
			}

			break;

		case 3:
			if (image.get_surface()->format->Rmask == 0x000000ff) {
				texture_format = GL_RGB;
			}
			else {
				texture_format = GL_BGR;
			}

			break;

		default:
			LOG4CXX_ERROR(log, L"" << filename << L" is not in true color! Could not handle that!");
			throw TextureColorDepthException(image.get_surface()->format->BytesPerPixel);
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures(1, &texture);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set the texture's stretching properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D(GL_TEXTURE_2D,
			     0,
			     image.get_surface()->format->BytesPerPixel,
			     image.get_surface()->w,
			     image.get_surface()->h,
			     0,
			     texture_format,
			     GL_UNSIGNED_BYTE,
			     image.get_surface()->pixels);
	}

	Texture::~Texture()
	{
		if (glIsTexture(texture)) {
			glDeleteTextures(1, &texture);
		}
	}

	GLuint Texture::get_texture(void) const
	{
		return texture;
	}
};
