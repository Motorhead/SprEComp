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

#include "Lexer.h"
#include "Tokens.h"
#include "SyntaxError.h"
#include <string>
#include <vector>

using namespace std;

Lexer::Lexer() :
	processed(false), lines()
{
}

Lexer::Lexer(string &data) :
	processed(false)
{
	lines = SplitLines(data);
}

Lexer::~Lexer()
{
	this->CleanTokens();
}

void Lexer::Feed(const string &data)
{
	processed = false;
	lines = SplitLines(data);
	this->CleanTokens();
}

bool Lexer::IsAlphaNumeric(const string &s) const
{
	for(string::const_iterator c = s.begin(); c < s.end(); c++)
		if(*c < 0x30 || (*c > 0x39 && *c < 0x41) || (*c > 0x5A && *c < 0x61) || *c > 0x7A)
			return false;
	return true;
}

bool Lexer::IsNumeric(const string &s) const
{
	for(string::const_iterator c = s.begin(); c < s.end(); c++)
		if(*c < 0x30 || *c > 0x39)
			return false;
	return true;
}

bool Lexer::IsString(const string &s) const
{
	if(s[0] == '"' && s[s.size() - 1] == '"')
		return true;
	return false;
}

vector<string> Lexer::SplitLines(const string &data)
{
	vector<string> lines;
	string s;
	bool comment = false;

	for(string::const_iterator c = data.begin(); c != data.end(); c++)
	{
		switch(*c)
		{
		case '\r':
		case '\n':
		case ';':
			if(s.size())
			{
				if(!comment)
					lines.push_back(s);
				s.clear();

				if(*c == ';')
					comment = true;
			}

			if((*c == '\r' || *c == '\n') && comment)
					comment = false;
			break;
		default:
			s += *c;
			c++;
			if(data.end() == c && s.size())
			{
				lines.push_back(s);
				s.clear();
			}
			c--;
		}
	}

	return lines;
}

vector<string> Lexer::SplitWords(const string &s)
{
	vector<string> words;
	string word;
	bool mark = false;

	for(string::const_iterator c = s.begin(); c != s.end(); c++)
	{
		switch(*c)
		{
		case '\t':
		case ' ':
		case ':':
		case ',':
			if(word.size() && !mark)
			{
				words.push_back(word);
				word.clear();
				
				if(*c == ':' || *c == ',')
					words.push_back(*c == ':' ? ":" : ",");
			}

			break;
		default:
			mark = *c == '"' ? !mark : mark;

			word += *c;
			c++;
			if(s.end() == c && word.size())
			{
				words.push_back(word);
				word.clear();
			}
			c--;
		}
	}

	return words;
}

string Lexer::LowerCase(const string &s)
{
	string z = s;

	for(string::iterator c = z.begin(); c < z.end(); c++)
		if(*c >= 0x41 && *c <= 0x5A)
			*c += 0x20;
	
	return z;
}

void Lexer::CleanTokens()
{
	for(vector<Statement>::iterator s = statements.begin(); s < statements.end(); s++)
		for(Statement::iterator t = s->begin(); t < s->end(); t++)
			delete *t;
	
	statements.clear();
}

vector<Statement>& Lexer::ProcessData()
{
	if(processed)
		return statements;

	vector<string> words;
	string s;
	Statement statement;
	vector<string>::iterator w;

	for(vector<string>::iterator line = lines.begin(); line < lines.end(); line++)
	{
		words = SplitWords(*line);
		
		if(words.size() < 1)
			continue;
		
		w = words.begin();
		s = LowerCase(*w);
		statement.clear();

		if(IsAlphaNumeric(s))
		{
			if(*(w + 1) == ":")
			{
				statement.push_back(new TTag(s));
				statement.push_back(new TOperator(":"));

				if(words.size() <= 2)
					goto push_back;

				w += 2;
				s = LowerCase(*w);
			}

			if(s == "img" || s == "frm")
			{
				statement.push_back(new TDirective(s));
				w++;
			}
			else if(s == "ren" || s == "jmp")
			{
				statement.push_back(new TCommand(s));
				w++;
			}
			else
				throw SyntaxError("'" + *w + "': unknown keyword on line:\n\t" + *line);

			for(; w < words.end(); w++)
			{
				if(IsString(*w))
					statement.push_back(new TString(*w));
				else if(IsNumeric(*w))
					statement.push_back(new TNumber(*w));
				else if(IsAlphaNumeric(*w))
					statement.push_back(new TName(*w));
				else if(*w == ",")
					statement.push_back(new TOperator(*w));
				else
					throw SyntaxError("'" + *w + "' in line:\n\t" + *line);
			}

push_back:	statements.push_back(statement);
		}
	}
	
	processed = true;

	return statements;
}