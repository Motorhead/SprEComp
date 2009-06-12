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

#include "TTag.h"
#include <string>

using namespace std;

TTag::TTag(const string &v) :
	Token("tag"), value(v)
{
}

TTag::TTag(const TTag &t) :
	Token("tag"), value(t.value)
{
}

TTag::TTag()
{
}

TTag::~TTag()
{
}

string TTag::GetValue()
{
	return value;
}

bool TTag::operator==(const TTag &b)
{
	if(value == b.value)
		return true;
	return false;
}
