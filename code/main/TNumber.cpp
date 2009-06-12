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

#include "TNumber.h"
#include <string>

using namespace std;

TNumber::TNumber(const string &v) :
	Token("number")
{
	value = StringToNumber(v);
}

TNumber::TNumber()
{
}

TNumber::~TNumber()
{
}

unsigned short TNumber::GetValue()
{
	return value;
}

unsigned short TNumber::StringToNumber(const std::string &s)
{
	unsigned short factor = 1;
	unsigned short number = 0;

	for(string::const_reverse_iterator c = s.rbegin(); c < s.rend(); c++, factor *= 10)
		number += (*c - 0x30)*factor;

	return number;
}