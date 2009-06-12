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

#ifndef TNAME_H
#define TNAME_H

#include "Token.h"
#include <string>

class TName :
	public Token
{
public:
	TName(const std::string &v);
	TName();
	virtual ~TName();
	std::string GetValue();
	bool operator==(const TName &b);

private:
	std::string value;
};

#endif // TNAME_H