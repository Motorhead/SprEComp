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

#include "TString.h"
#include <string>

using namespace std;

TString::TString(const string &v) :
	Token("string")
{
	value = RemoveMarks(v);
}

TString::TString()
{
}

TString::~TString()
{
}

string TString::RemoveMarks(const std::string &s)
{
	string a = s;
	if(s.length() > 2)
		return a.substr(1, a.size() - 2);
	
	return a;
}

string TString::GetValue()
{
	return value;
}
