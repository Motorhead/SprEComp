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

#ifndef TDIRECTIVE_H
#define TDIRECTIVE_H

#include "Token.h"
#include <string>

class TDirective :
	public Token
{
public:
	TDirective(const std::string &v);
	TDirective();
	virtual ~TDirective();
	std::string GetValue();
	bool operator==(const TDirective &b);

private:
	std::string value;
};

#endif // TDIRECTIVE_H