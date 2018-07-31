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
#ifndef KONGOAPPLICATION_H
#define KONGOAPPLICATION_H
#include "kongoscene.h"
namespace Kongomato
{
class DLL_DECLSPEC Application
{  
   protected:
    virtual void Draw()=0;
    virtual void Idle()=0;
    bool terminated;
   public:
    Application(int argc,char* argv[]);
    void Run();

};
}

#endif // KONGOAPPLICATION_H
