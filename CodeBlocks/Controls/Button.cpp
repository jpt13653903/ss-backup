//==============================================================================
// Copyright (C) John-Philip Taylor
// jpt13653903@gmail.com
//
// This file is part of Simply-Scripted Backup
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#include "Button.h"
//------------------------------------------------------------------------------

BUTTON::BUTTON(
 int Left, int Top, int Width, const wchar_t* Caption
): CONTROL(
 WC_BUTTON, WS_TABSTOP | BS_PUSHBUTTON, Left, Top, Width, 21
){
 SetCaption(Caption);
}
//------------------------------------------------------------------------------

BUTTON::~BUTTON(){
}
//------------------------------------------------------------------------------
