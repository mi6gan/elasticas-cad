/***************************************************************************
 *   Copyright (C) 2010 by Michael Boyarov                                 *
 *   mi666gan@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef WITH_SDL
#include "kongoinput.h"
namespace Kongomato { namespace Input {
Keyboard::Keyboard()
{
    changed=true;    
    key_states.resize((int)SDLK_LAST);
    for(int a=0;a<key_states.size();a++) key_states[a]=KeyUp;

}

Keyboard::~Keyboard()
{
}

const std::wstring & Keyboard::GetKeysSymBuffer()
{
    return sym_buffer;
}

const std::vector<KeyState> & Keyboard::GetKeysState()
{
    return key_states;
}

void Keyboard::Update(SDL_Event * event,bool clear_keys_sym_buffer)
{    
    if(clear_keys_sym_buffer) sym_buffer.clear();
    SDL_KeyboardEvent * key_event=(SDL_KeyboardEvent *)event;
    int size=key_states.size();
    int key_sym;
    if(key_event->type==SDL_KEYDOWN)
    {
        key_sym=(int)key_event->keysym.sym;
        sym_buffer=sym_buffer+((wchar_t)key_event->keysym.unicode);
        key_states[key_sym]=KeyDown;
    }
    else if(key_event->type==SDL_KEYUP)
    {
        key_sym=(int)key_event->keysym.sym;
        key_states[key_sym]=KeyUp;
    }
}
//___________________________________________________________________________
void Mouse::Update(SDL_Event * event)
{
}
//___________________________________________________________________________
Manager* Manager::self=NULL;

Manager::Manager()
{
    SDL_Init(SDL_INIT_VIDEO);
//    SDL_WM_GrabInput(SDL_GRAB_ON);
}

Manager* Manager::Instance()
{
    if(!self) self=new Manager();
    return self;
}

void Manager::Update(bool clear_keys_sym_buffer)
{

    while( SDL_PollEvent( &event ) )
    {

        if(event.type==SDL_KEYDOWN||event.type==SDL_KEYUP)
        {
            int size=keyboards.size();
            for(int a=0;a<size;a++) keyboards[a]->Update(&event,clear_keys_sym_buffer);
        }
        else  if(event.type==SDL_MOUSEMOTION||event.type==SDL_MOUSEBUTTONUP||event.type==SDL_MOUSEBUTTONDOWN)
        {
            int size=mice.size();
            for(int a=0;a<size;a++) mice[a]->Update(&event);
        }
    }
}

Keyboard* Manager::GenerateKeyboard()
{
    keyboards.push_back(new Keyboard);
    return keyboards.back();
}

Mouse* Manager::GenerateMouse()
{
    mice.push_back(new Mouse);
    return mice.back();
}

Manager::~Manager()
{
    int size=keyboards.size();
    for(int a=0;a<size;a++) delete keyboards[a];
    size=mice.size();
    for(int a=0;a<size;a++) delete mice[a];
}

} }
#endif
