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

#include "Parser.h"
#include "Tokens.h"
#include "Image.h"
#include <cstring>

using namespace std;

/*
	NOTE: Change this cuz it's ugly, big & gay.
*/
Parser::Parser()
{
	img.push_back(new TDirective("img"));
	img.push_back(new TName(""));
	img.push_back(new TOperator(","));
	img.push_back(new TString(""));

	frm.push_back(new TDirective("frm"));
	frm.push_back(new TName(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TName(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));

	ren.push_back(new TCommand("ren"));
	ren.push_back(new TName(""));

	rend.push_back(new TCommand("ren"));
	rend.push_back(new TName(""));
	rend.push_back(new TOperator(","));
	rend.push_back(new TNumber(""));

	jmp.push_back(new TCommand("jmp"));
	jmp.push_back(new TName(""));

	spreData = NULL;
}

Parser::Parser(const vector<Statement> &s) :
	statements(s)
{
	img.push_back(new TDirective("img"));
	img.push_back(new TName(""));
	img.push_back(new TOperator(","));
	img.push_back(new TString(""));

	frm.push_back(new TDirective("frm"));
	frm.push_back(new TName(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TName(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));
	frm.push_back(new TOperator(","));
	frm.push_back(new TNumber(""));

	ren.push_back(new TCommand("ren"));
	ren.push_back(new TName(""));

	rend.push_back(new TCommand("ren"));
	rend.push_back(new TName(""));
	rend.push_back(new TOperator(","));
	rend.push_back(new TNumber(""));

	jmp.push_back(new TCommand("jmp"));
	jmp.push_back(new TName(""));

	spreData = NULL;
}

void Parser::Feed(const vector<Statement> &s)
{
	statements = s;
}

Parser::~Parser()
{
	Statement::iterator i;
	for(i = img.begin(); i < img.end(); delete *(i++));
	for(i = frm.begin(); i < frm.end(); delete *(i++));
	for(i = ren.begin(); i < ren.end(); delete *(i++));
	for(i = rend.begin(); i < rend.end(); delete *(i++));
	for(i = jmp.begin(); i < jmp.end(); delete *(i++));

	if(spreData != NULL)
		delete spreData;
}



void Parser::CheckSyntax(const Statement &x, const Statement &y)
{
	if(x.size() != y.size())
		throw SizeError("Wrong number of arguments");

	Statement::const_iterator a;
	Statement::const_iterator b;
	TOperator &opa = TOperator("");
	TOperator &opb = TOperator("");

	for(a = x.begin(), b = y.begin(); a < x.end(); a++, b++)
	{
		if((*a)->GetName() != (*b)->GetName())
			throw SyntaxError("expected '" + (*b)->GetName() + "' but got '" + (*a)->GetName() + "'.");

		if((*a)->GetName() == "operator")
		{
			opa = *(static_cast<TOperator*>(*a));
			opb = *(static_cast<TOperator*>(*b));

			if(!(opa == opb))
				SyntaxError("expected '" + opb.GetValue() + "' but got '" + opa.GetValue() + "'.");
		}
	}
}

// std::map::find EPIC FAOLS
bool Parser::IsTagDeclared(TTag &t)
{
	string a;
	map<string, int>::iterator i;
	for(i = tags.begin(); i != tags.end(); i++)
	{
		a = i->first;	

		if(a == t.GetValue())
			return true;
	}
	return false;
}

bool Parser::IsNameDeclared(TName &n)
{
	for(vector<TName>::iterator i = names.begin(); i != names.end(); i++)
		if(n == *i)
			return true;
	return false;
}

unsigned short Parser::GetFrameIndex(TName &n)
{
	map<string, Frame>::iterator i;
	unsigned short idx = 0;
	for(i = frames.begin(); i != frames.end(); i++, idx++)
		if(i->first == n.GetValue())
			return idx;
	return idx;
}

SprEData *Parser::ProcessData()
{
	bool code = false;
	int index = 0, codeOffset;
	
	for(vector<Statement>::iterator s = statements.begin(); s < statements.end(); s++, index++)
	{
		// Check if there's a tag, store it and remove it from the statement line if present.
		if((*s)[1]->GetName() == "operator")
			if(static_cast<TOperator*>((*s)[1])->GetValue() == ":" && (*s)[0]->GetName() == "tag")
			{
				TTag tag(*static_cast<TTag*>((*s)[0]));
				
				if(!IsTagDeclared(tag))
					tags[tag.GetValue()] = index;
				else
					throw SyntaxError("Tag has been redefined.\n\t" + tag.GetValue());

				(*s).erase((*s).begin(), (*s).begin() + 2);
				
				if(!s->size())
					throw SyntaxError("Empty Tag\n\t" + tag.GetValue());
				
				if((*s)[0]->GetName() != "command")
					throw SyntaxError("Tags can only be declared on ren commands.");
				
				if(static_cast<TCommand*>((*s)[0])->GetValue() != "ren")
					throw SyntaxError("Tags can only be declared on ren commands.");
			}
			else
				throw SyntaxError("Wrong operator.");

		if((*s)[0]->GetName() == "directive")
		{
			if(code)
				throw SyntaxError("directives must be declared before any command.");
			
			TDirective *directive = static_cast<TDirective*>((*s)[0]);
			if(directive->GetValue() == "img")
			{
				CheckSyntax(*s, img);

				// img name, location
				TName iname = *static_cast<TName*>((*s)[1]);
				TString location = *static_cast<TString*>((*s)[3]);

				if(IsNameDeclared(iname))
					throw SyntaxError("name has been already declared.\n\t" + iname.GetValue());

				names.push_back(iname);
				images[iname.GetValue()] = Image(location.GetValue());
			}
			else
			{
				CheckSyntax(*s, frm);

				// frm name, imagename, x, y, w, h, d
				TName fname = *static_cast<TName*>((*s)[1]);
				TName iname = *static_cast<TName*>((*s)[3]);
				TNumber x = *static_cast<TNumber*>((*s)[5]);
				TNumber y = *static_cast<TNumber*>((*s)[7]);
				TNumber w = *static_cast<TNumber*>((*s)[9]);
				TNumber h = *static_cast<TNumber*>((*s)[11]);
				TNumber d = *static_cast<TNumber*>((*s)[13]);

				if(IsNameDeclared(fname))
					throw SyntaxError("name has been declared more than once.\n\t" + fname.GetValue());

				if(!IsNameDeclared(iname))
					throw SyntaxError("image has not been declared.\n\t" + iname.GetValue());

				if(images.find(iname.GetValue()) == images.end())
					throw SyntaxError("image has not been declared.\n\t" + iname.GetValue());

				names.push_back(fname);
				frames[fname.GetValue()] = Frame();
				frames[fname.GetValue()].x = x.GetValue();
				frames[fname.GetValue()].y = y.GetValue();
				frames[fname.GetValue()].w = w.GetValue();
				frames[fname.GetValue()].h = h.GetValue();
				frames[fname.GetValue()].d = d.GetValue();
				frames[fname.GetValue()].p = images[iname.GetValue()].GetFramePixelData(frames[fname.GetValue()]);
			}
		}
		else if((*s)[0]->GetName() == "command")
		{
			TCommand *command = static_cast<TCommand*>((*s)[0]);
			static FrameSequenceControl fsc;

			if(command->GetValue() == "jmp")
			{
				CheckSyntax(*s, jmp);

				// jmp tag
				TTag tag(static_cast<TName*>((*s)[1])->GetValue());

				if(!IsTagDeclared(tag))
					throw SyntaxError("tag has not been declared.\n\t" + tag.GetValue());

				fsc.tag = tags[tag.GetValue()] - codeOffset;
				fsc.opcode = op_jmp;

				sprite.push_back(fsc);
			}
			else
			{
				try
				{
					CheckSyntax(*s, ren);

					// ren frm
					TName frame = *static_cast<TName*>((*s)[1]);

					if(!IsNameDeclared(frame))
						throw SyntaxError("frame has not been declared.\n\t" + frame.GetValue());

					if(frames.find(frame.GetValue()) == frames.end())
						throw SyntaxError("frame has not been declared.\n\t" + frame.GetValue());

					fsc.opcode = op_ren;
					fsc.frame = GetFrameIndex(frame);

					sprite.push_back(fsc);
				}
				catch(...)
				{
					CheckSyntax(*s, rend);

					// ren frm, d
					TName frame = *static_cast<TName*>((*s)[1]);
					TNumber d = *static_cast<TNumber*>((*s)[3]);

					if(!IsNameDeclared(frame))
						throw SyntaxError("frame has not been declared.\n\t" + frame.GetValue());

					if(frames.find(frame.GetValue()) == frames.end())
						throw SyntaxError("frame has not been declared.\n\t" + frame.GetValue());

					fsc.opcode = op_rend;
					fsc.frame = GetFrameIndex(frame);
					fsc.duration = d.GetValue();

					sprite.push_back(fsc);
				}
			}

			if(!code)
			{
				code = true;
				codeOffset = index;
			}
		}
		else
			throw SyntaxError("statements must begin with either a directive, a command or a tag.");
	}

	if(spreData != NULL)
		delete spreData;

	spreData = new SprEData;

	for(map<string, Frame>::iterator i = frames.begin(); i != frames.end(); i++)
		spreData->frames.push_back(i->second);

	spreData->sprite = sprite;

	return spreData;
}