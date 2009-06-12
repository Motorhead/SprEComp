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

#include "Image.h"
#include "ILError.h"

using namespace std;

bool Image::ILinitialized = false;
bool Image::ILUinitialized = false;

Image::Image()
{
}

Image::Image( const string &location)
{
	if(!ILinitialized && !ILUinitialized)
	{
		ilInit();
		iluInit();

		// Ensure all images are loaded with the origin in the
		// upper left corner, which is SprE's convention.
		ilEnable(IL_ORIGIN_SET);
		ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);

		Image::ILinitialized = true;
		Image::ILUinitialized = true;
	}

	ILenum error;
	img = ilGenImage();
	ilBindImage(img);
	ilLoadImage(location.c_str());
	
	if(IL_NO_ERROR != (error = ilGetError()))
		throw ILError(iluErrorString(error));

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);


	unsigned int *data = new unsigned int[width*height];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, (void*)data);

	for(int j = 0; j < height; j++)
		for(int i = 0; i < width*4; i += 4)
			pixelData.push_back(Image::RGBA32to16((unsigned char*)data + j*width*4 + i));

	delete [] data;
}

Image::~Image()
{
	ilDeleteImage(img);
}

vector<unsigned short> Image::GetFramePixelData(struct Frame &f)
{
	vector<unsigned short> v;

	if(f.x > width || f.y > height || (f.x + f.w) > width || (f.y + f.h) > height)
		throw ILError("frame has invalid dimensions");
	if(f.x < 0 || f.y < 0 || (f.x + f.w) <= 0 || (f.y + f.h) <= 0)
		throw ILError("frame has invalid dimensions");

	for(int j = 0; j < f.h; j++)
		for(int i = 0; i < f.w; i++)
			v.push_back(pixelData[(j + f.y)*width + i + f.x]);

	return v;
}

vector<unsigned short> Image::GetPixelData()
{
	return pixelData;
}

unsigned short Image::GetWidth()
{
	return width;
}

unsigned short Image::GetHeight()
{
	return height;
}

Image& Image::operator=(const Image &i)
{
	pixelData = i.pixelData;
	width = i.width;
	height = i.height;

	return *this;
}

unsigned short Image::RGBA32to16(const unsigned char *data)
{
	unsigned short R, G, B, A;

	R = (unsigned short)(data[0]*32.0f/256.0f + 0.5f);
	G = (unsigned short)(data[1]*32.0f/256.0f + 0.5f);
	B = (unsigned short)(data[2]*32.0f/256.0f + 0.5f);
	A = data[3] == 0 ? 0 : 1; 

	return ((A << 15) | (B << 10) | (G << 5) | R);
}
