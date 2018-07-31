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
#include "kongoapplication.h"
#include "kongoinput.h"
#include "kongosprite.h"
#undef GetObjectA
class Application: public Kongomato::Application
{
    Kongomato::Input::Keyboard* keyboard;
    Kongomato::TwoDimensional::Sprite* sprite;
    Kongomato::VideoDevice::Texture* texture;
    int t;
    void Draw()
    {
        using namespace Kongomato;
        VideoDevice::Manager* device=VideoDevice::Manager::Instance();
        device->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);        
        texture->Draw();//Math::Rectangle<int>(),Math::Rectangle<int>(),VideoDevice::texture_draw_flip);

 /*       TwoDimensional::PrimitivesPlotter::BeginDraw(GL_LINES);
        glVertex2f(-1.0f,-1.0f);
        glVertex2f(1.0f,1.0f);
        TwoDimensional::PrimitivesPlotter::EndDraw();*/
        //device->SetCurrentDrawTarget();
        device->Present();
    }

    void Idle()
    {
        Kongomato::Input::Manager * input_device=Kongomato::Input::Manager::Instance();
        input_device->Update();       
        if(keyboard->GetKeysState()[SDLK_ESCAPE]==Kongomato::Input::KeyDown)
        {            
            terminated=true;
        }
        t++;
    }
   public:
    Application(int argc,char* argv[]):Kongomato::Application(argc,argv)
    {        
        t=0;
        using namespace Kongomato;
        VideoDevice::Manager* device=VideoDevice::Manager::Instance();
        Kongomato::Input::Manager* input_device=Kongomato::Input::Manager::Instance();
        keyboard=input_device->GenerateKeyboard();
        device->ChangeContext(VideoDevice::SDL_Context,Base::VideoMode(1024,768,true,false,32));
   //     texture=new VideoDevice::Texture("media/a.png");

        texture=new VideoDevice::Texture("media/texture1.png");
        VideoDevice::Texture* tmp_texture=new VideoDevice::Texture("/home/mi6gan/Pictures/Cherry_tree_by_NoDate.jpg");

        device->SetCurrentDrawTarget(texture);
        //device->Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        tmp_texture->Draw(Math::Rectangle<int>(0,0,128,128));
        device->Present();
        device->SetCurrentDrawTarget();
        device->SetClearColor(0,0,0.5f,0);
    }

    ~Application()
    {
    }
};

int main(int argc,char* argv[])
{
        Application app(argc,argv);
        app.Run();
	return 0;
}
