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

#include "Compiler.h"
#include "FileError.h"
#include <string>
#include <fstream>

using namespace std;

string Compiler::Capitalize(const string &s)
{
	string z = s;

	for(string::iterator c = z.begin(); c < z.end(); c++)
		if(*c >= 0x61 && *c <= 0x7A)
			*c -= 0x20;
	
	return z;
}

Compiler::Compiler()
{
}

Compiler::~Compiler()
{
}

Compiler::Compiler(const string &d) :
	data(d)
{
}

void Compiler::FeedString(const string &d)
{
	data = d;
}

void Compiler::FeedFromFile(const string &filename)
{
	ifstream source(filename.c_str());
	string line;

	if(!source.is_open())
		throw FileError(filename + " was not found.");

	while(!source.eof())
	{
		getline(source, line);
		data += line + "\n";
	}

	source.close();
}

void Compiler::Compile()
{
	lexer.Feed(data);
	code = lexer.ProcessData();

	parser.Feed(code);
	parser.ProcessData();
}

void Compiler::SaveToFile(const string &filename)
{
	ofstream output((filename + ".h").c_str());

	if(!output.is_open())
		throw FileError("couldn't create file " + filename);

	output << "#ifndef " + Compiler::Capitalize(filename) + "_H" << endl;
	output << "#define " + Compiler::Capitalize(filename) + "_H" << endl;
	output << endl << "#include \"Frame.h\"" << endl;
	output << endl << "unsigned short " + filename + "_nframes = " << parser.spreData->frames.size() << ";" << endl << endl;
	output << "struct Frame " + filename + "_frames[] = {";

	for(unsigned int i = 0; i < parser.spreData->frames.size(); i++)
	{
		if(i != 0)
			output << ", " << endl;

		output << endl << "{";
		output << parser.spreData->frames[i].x << ", ";
		output << parser.spreData->frames[i].y << ", ";
		output << parser.spreData->frames[i].w << ", ";
		output << parser.spreData->frames[i].h << ", ";
		output << parser.spreData->frames[i].d << ", {" << endl;

		for(unsigned int j = 0; j < parser.spreData->frames[i].p.size(); j++)
		{
			if(j != 0)
			{
				output << ", ";
				if((j + 1) % 10 == 0)
					output << endl;
			}

			output << parser.spreData->frames[i].p[j];
		}

		output << "}}";
	}

	output << "};" << endl;

	output << endl << "int " + filename + "_sprite_size = " << parser.spreData->sprite.size() << ";" << endl;

	output << endl << "Sprite " + filename + "_sprite = {";
	for(unsigned int i = 0; i < parser.spreData->sprite.size(); i++)
	{
		if(i != 0)
			output << ", ";

		output << endl << "{";
		output << parser.spreData->sprite[i].opcode << ", ";
		output << parser.spreData->sprite[i].frame << ", ";
		output << parser.spreData->sprite[i].duration << "}";
		
	}
	output << "};" << endl;

	output << endl << "#endif // " + Compiler::Capitalize(filename) + "_H" << endl;


	output.close();
}
