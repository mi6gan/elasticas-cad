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
#include "kongosprite.h"
namespace Kongomato
{
namespace TwoDimensional
{
    Math::Matrix4x4<float> vm;
    Math::Matrix4x4<float> wm;
    Math::Matrix4x4<float> pm;
    Math::Matrix4x4<float> id;
    bool lighting;
    bool culling;
    VideoDevice::Context::ViewportRectangleBehavior PrimitivesPlotter::last_vrb=VideoDevice::Context::SimpleVRBehavior;
    void PrimitivesPlotter::BeginDraw(GLenum mode,const Math::Matrix4x4<float> & mat)
    {        
        Kongomato::VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance(); 
        lighting=dev->GetBoolParameter(VideoDevice::lighting_parameter);
        culling=dev->GetBoolParameter(VideoDevice::cullface_parameter);
        if(lighting) dev->SetBoolParameter(VideoDevice::lighting_parameter,false);
        if(culling) dev->SetBoolParameter(VideoDevice::cullface_parameter,false);
        dev->SetTransform(VideoDevice::world2d_transformation,mat);
        dev->ApplyTransformations(VideoDevice::Manager::Matrix2DMode);
        last_vrb=dev->GetCurrentContext()->GetViewportRectangleBehavior();
        dev->GetCurrentContext()->SetViewportRectangleBehavior(VideoDevice::Context::SimpleVRBehavior);        
        glBegin(mode);
    }

    void PrimitivesPlotter::EndDraw()
    {
        Kongomato::VideoDevice::Manager* dev=Kongomato::VideoDevice::Manager::Instance();        
        glEnd();        
        dev->GetCurrentContext()->SetViewportRectangleBehavior(last_vrb);
        if(culling) dev->SetBoolParameter(VideoDevice::cullface_parameter,culling);
        if(lighting) dev->SetBoolParameter(VideoDevice::lighting_parameter,lighting);
    }


//___________________________________________________________________________
    Sprite::Sprite(const std::string & filename)
    {
        using namespace Kongomato::VideoDevice;
        texture=new Texture(filename);
    }

    void Sprite::Draw()
    {
        using namespace Kongomato::VideoDevice;
        texture->Draw();
    }

    Sprite::~Sprite()
    {
        delete texture;
    }

}
}
