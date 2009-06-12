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


#include "SizeError.h"
#include "SyntaxError.h"
#include "ILError.h"
#include "FileError.h"
#include "Compiler.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout << "USAGE: sprecomp [input]" << endl;
		return 0;
	}

	Compiler compiler;
	
	try
	{
		compiler.FeedFromFile(string(argv[1]) + ".s");
	}
	catch(FileError &e)
	{
		cout << e.what() << endl;
		return 0;
	}

	try
	{
		compiler.Compile();
		compiler.SaveToFile(string(argv[1]));
	}
	catch(SizeError &e)
	{
		cout << e.what() << endl;
		return 0;
	}
	catch(SyntaxError &e)
	{
		cout << e.what() << endl;
		return 0;
	}
	catch(ILError &e)
	{
		cout << e.what() << endl;
		return 0;
	}

	cout << "Compilation process ended succesfully." << endl;
	return 0;
}