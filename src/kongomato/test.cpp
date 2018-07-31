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
#undef GetObjectA
class Application: public Kongomato::Application
{
    Kongomato::Scene::Manager* scene;
    Kongomato::Input::Keyboard* keyboard;
    Kongomato::Scene::SimpleMesh* mesh;
    Kongomato::VideoDevice::Texture* texture;
    void Draw()
    {
        using namespace Kongomato;
        VideoDevice::Manager* device=VideoDevice::Manager::Instance();

        scene->Draw();

    }

    void Idle()
    {
        Kongomato::Input::Manager * input_device=Kongomato::Input::Manager::Instance();
        input_device->Update();
        std::vector<Kongomato::Input::KeyState> keys=keyboard->GetKeysState();
        if(keys[SDLK_ESCAPE]==Kongomato::Input::KeyDown) terminated=true;
        if(keys[SDLK_UP]==Kongomato::Input::KeyDown) scene->GetCamera().Rotate(0.001f,0,0);
    }
   public:
    Application(int argc,char* argv[]):Kongomato::Application(argc,argv)
    {
        using namespace Kongomato;        
        VideoDevice::Manager* device=VideoDevice::Manager::Instance();                
        device->ChangeContext(VideoDevice::SDL_Context,Base::VideoMode(640,480,true,false,32));
        scene=new Kongomato::Scene::Manager("scene1");                
        mesh=
        scene->AddSimpleMesh("media/unit1.fm3");
        mesh->SetName("mesh1");
        scene->SetCameraTaget(mesh);
        device->SetTransform(VideoDevice::projection_transformation,Math::Matrix4x4<float>::PerspectiveView(M_PI/3.0f,4.0f/3.0f,1.0f,100.0f));
        scene->GetCamera().SetDist(20);
        scene->SetBackgroundColor(Kongomato::Base::Color<double>(0.5f,0.5f,0.5f,1.0f));

        Kongomato::Input::Manager* input_device=Kongomato::Input::Manager::Instance();
        keyboard=input_device->GenerateKeyboard();

        texture=new VideoDevice::Texture("media/texture1.png");        
    }

    ~Application()
    {
        using namespace Kongomato;
        VideoDevice::Manager* device=VideoDevice::Manager::Instance();
        delete scene;
        device->Destroy();
    }
};
int main(int argc,char* argv[])
{
    Application app(argc,argv);
    app.Run();
    return 0;
}

