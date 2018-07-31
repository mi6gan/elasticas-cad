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
#include "kongovideodevice.h"
#include <string>
#ifndef TWO_DIMENSIONAL_H
#define TWO_DIMENSIONAL_H
namespace Kongomato
{
namespace TwoDimensional
{
class DLL_DECLSPEC PrimitivesPlotter
{
    static VideoDevice::Context::ViewportRectangleBehavior last_vrb;
   public:
    static void BeginDraw(GLenum mode,const Math::Matrix4x4<float> & mat=Math::Matrix4x4<float>());
    static void EndDraw();
    static void DrawPolyline(std::vector<Math::Vector2D<float> > & polyline);
};

class DLL_DECLSPEC Sprite
{
     Kongomato::VideoDevice::Texture* texture;
    public:
     Sprite(const std::string & filename);
     ~Sprite();
     void Draw();
};

}
}
#endif
