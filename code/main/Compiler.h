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

#ifndef COMPILER_H
#define COMPILER_H

#include "Lexer.h"
#include "Parser.h"

class Compiler
{
public:
	Compiler();
	Compiler(const std::string &d);
	void FeedString(const std::string &d);
	void FeedFromFile(const std::string &filename);
	void Compile();
	void SaveToFile(const std::string &filename);
	~Compiler();
private:
	static std::string Capitalize(const std::string &s);
	std::string data;
	std::vector<Statement> code;
	Lexer lexer;
	Parser parser;

};

#endif // COMPILER_H