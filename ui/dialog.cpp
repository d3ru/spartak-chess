/*
Spartak Chess based on stockfish engine.
Copyright (C) 2010 djdron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "dialog.h"
#include <algorithm>

eFont* eDialog::font = NULL;

void eDialog::Destroy()
{
	for(eDialogs::iterator i = childs.begin(); i != childs.end(); ++i)
	{
		(*i)->Destroy();
		delete *i;
	}
	childs.clear();
}

void eDialog::Paint(eBufferRGBA& buf)
{
	buf.Clear(bound);
	if(!text.empty())
		font->DrawText(buf, bound.beg, text.c_str());
	for(eDialogs::iterator i = childs.begin(); i != childs.end(); ++i)
	{
		(*i)->Paint(buf);
	}
}
void eDialog::Remove(eDialog* child)
{
	eDialogs::iterator i = std::find(childs.begin(), childs.end(), child);
	if(i != childs.end())
		childs.erase(i);
}

eDesktop::eDesktop() : focus(NULL), buffer(ePoint2(320, 240))
{
	font = new eFont;
}
eDesktop::~eDesktop()
{
	delete font;
}
void eDesktop::Update()
{
	Paint(buffer);
}