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

#ifndef LEXER_H
#define LEXER_H

#include "Statement.h"
#include <string>
#include <vector>

class Lexer
{
public:
	std::vector<Statement> statements;

	Lexer();
	Lexer(std::string &data);
	~Lexer();
	void Feed(const std::string &data);
	std::vector<Statement>& ProcessData();

private:
	std::vector<std::string> lines;
	bool processed;

	bool IsAlphaNumeric(const std::string &s) const;
	bool IsNumeric(const std::string &s) const;
	bool IsString(const std::string &s) const;
	std::vector<std::string> SplitLines(const std::string &data);
	std::vector<std::string> SplitWords(const std::string &s);
	std::string LowerCase(const std::string &s);
	void CleanTokens();
};

#endif // LEXER_H