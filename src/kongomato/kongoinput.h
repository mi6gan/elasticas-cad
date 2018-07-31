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
#include <vector>
#include <string>
#include <iostream>
#include <SDL.h>
#include "kongobase.h"
namespace Kongomato { namespace Input {
enum KeyState
{
  //  KeyPressed=0,
 //   KeyReleased=1,
    KeyUp=0,
    KeyDown=1,
    KeyStateLast
};

class DLL_DECLSPEC Keyboard
{
    friend class Manager;
    bool changed;
    std::wstring sym_buffer;
    std::vector<KeyState> key_states;
    void Update(SDL_Event * event,bool clear_keys_sym_buffer=true);
    Keyboard();
    ~Keyboard();
   public:
    const std::wstring & GetKeysSymBuffer();
    const std::vector<KeyState> & GetKeysState();
};

class DLL_DECLSPEC Mouse
{
    friend class Manager;
    void Update(SDL_Event * event);
   public:

};

class DLL_DECLSPEC Manager
{
    SDL_Event event;
    std::vector<Keyboard*> keyboards;
    std::vector<Mouse*> mice;
    static Manager * self;
    Manager();
   public:
    void Update(bool clear_keys_sym_buffer=true);
    static Manager* Instance();
    Keyboard* GenerateKeyboard();
    Mouse* GenerateMouse();
    ~Manager();
};



}}
#endif
