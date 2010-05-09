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

#include "frame_background_image.hpp"

namespace usdx
{
	FrameBackgroundImage::FrameBackgroundImage(boost::filesystem::wpath filename)
	{
		texture = new Texture(filename);

		this->vertices[0] = 0.0f;
		this->vertices[1] = 600.0f;
		this->vertices[2] = 0.0f;
		this->vertices[3] = 800.0f;
		this->vertices[4] = 600.0f;
		this->vertices[5] = 0.0f;
		this->vertices[6] = 800.0f;
		this->vertices[7] = 0.0f;
		this->vertices[8] = 0.0f;
		this->vertices[9] = 0.0f;
		this->vertices[10] = 0.0f;
		this->vertices[11] = 0.0f;

		this->color[0] = 255;
		this->color[1] = 255;
		this->color[2] = 255;
		this->color[3] = 255;
		this->color[4] = 255;
		this->color[5] = 255;
		this->color[6] = 255;
		this->color[7] = 255;
		this->color[8] = 255;
		this->color[9] = 255;
		this->color[10] = 255;
		this->color[11] = 255;
		this->color[12] = 255;
		this->color[13] = 255;
		this->color[14] = 255;
		this->color[15] = 255;

		this->tex[0] = 0.0f;
		this->tex[1] = 1.0f;
		this->tex[2] = 1.0f;
		this->tex[3] = 1.0f;
		this->tex[4] = 1.0f;
		this->tex[5] = 0.0f;
		this->tex[6] = 0.0f;
		this->tex[7] = 0.0f;
	}

	FrameBackgroundImage::~FrameBackgroundImage()
	{
		delete texture;
	}

	void FrameBackgroundImage::draw(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, texture->get_texture());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
		glTexCoordPointer(2, GL_FLOAT, 0, tex);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
};
