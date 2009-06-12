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

#ifndef PARSER_H
#define PARSER_H

#include "SyntaxError.h"
#include "SizeError.h"
#include "Statement.h"
#include "Tokens.h"
#include "Frame.h"
#include "Image.h"
#include <map>
#include <vector>

struct SprEData
{
	std::vector<Frame> frames;
	Sprite sprite;
};

class Parser
{
public:
	SprEData *spreData;

	Parser();
	Parser(const std::vector<Statement> &s);
	void Feed(const std::vector<Statement> &s);
	SprEData *ProcessData();
	~Parser();
private:
	std::vector<Statement> statements;
	Sprite sprite;

	std::map<std::string, int> tags;
	std::map<std::string, Frame> frames;
	std::map<std::string, Image> images;
	std::vector<TName> names;

	Statement img;
	Statement frm;
	Statement ren;
	Statement rend;
	Statement jmp;

	void CheckSyntax(const Statement &x, const Statement &y);
	bool IsTagDeclared(TTag &t);
	bool IsNameDeclared(TName &n);
	unsigned short GetFrameIndex(TName &n);
};

#endif // PARSER_H