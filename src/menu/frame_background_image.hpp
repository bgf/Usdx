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

#ifndef FRAME_BACKGROUND_IMAGE_HPP
#define FRAME_BACKGROUND_IMAGE_HPP

#include <boost/filesystem.hpp>
#include <GL/gl.h>

#include "frame_background.hpp"
#include "texture.hpp"

namespace usdx
{
	class FrameBackgroundImage : public FrameBackground
	{
	private:
		Texture* texture;

		GLfloat vertices[12];
		GLubyte color[16];
		GLfloat tex[8];

	protected:
		void draw(void);

	public:
		FrameBackgroundImage(boost::filesystem::wpath filename);
		virtual ~FrameBackgroundImage();
	};
};


#endif
