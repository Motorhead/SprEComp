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

#ifndef FRAME_H
#define FRAME_H

#include <vector>

struct FrameData;
struct FrameSequenceControl;
typedef std::vector<struct FrameSequenceControl> Sprite;

enum FrameOpcodes
{
	op_ren = 0x0A,
	op_rend,
	op_jmp
};

struct FrameSequenceControl
{
	enum FrameOpcodes opcode;
	union
	{
		struct
		{
			unsigned short frame;
			unsigned short duration;
		};
		unsigned short tag;
	};
};

struct Frame
{
	unsigned short x, y, w, h, d;
	std::vector<unsigned short> p;
};

#endif // FRAME_H