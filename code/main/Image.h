// ===========================================================================
// Copyright (C) 2009  Edgar Antonio Rodriguez Velazco
//
//  This file is part of SprEComp.
//
//  SprEComp is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  SprEComp is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SprEComp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

#ifndef IMAGE_H
#define IMAGE_H

#include "Frame.h"
#include <string>
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>

class Image
{
	static bool ILinitialized;
	static bool ILUinitialized;

public:
	Image();
	Image(const std::string &location);
	~Image();
	std::vector<unsigned short> GetFramePixelData(struct Frame &f);
	std::vector<unsigned short> GetPixelData();
	unsigned short GetWidth();
	unsigned short GetHeight();
	Image& operator=(const Image &i);

private:
	unsigned short width, height;
	ILuint img;
	std::vector<unsigned short> pixelData;

	static unsigned short RGBA32to16(const unsigned char *data);
};

#endif // IMAGE_H