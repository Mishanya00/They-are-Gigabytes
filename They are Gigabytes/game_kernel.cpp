#include "game_kernel.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"

#include "shaders.hpp"
#include "interface_technique.hpp"

#include "meshes_manager.hpp"

#include "interface.hpp"
#include "freetypeGL.h"

#include "scenario.hpp"

struct Vertex
{
    Vector3f pos;
    Vector2f tex_coord;

    Vertex() {}

    Vertex(const Vector3f& position, const Vector2f& texture_coord)
    {
        this->pos = position;
        this->tex_coord = texture_coord;
    }
};

int ClientWidth = 1920;
int ClientHeight = 1080;

std::vector<std::unique_ptr<rgl::Panel>> ComponentsList; // array of pointers to allow polymorphism
std::shared_ptr<rgl::FontRenderer> Font;
std::unique_ptr<Scenario> ActiveScenario;

InterfaceTechnique* InterfaceShader;


void KeyboardHandler(unsigned char key, int x, int y)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnKeyboard(key);

    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

void KeyboardSpecialHandler(int key, int x, int y)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnKeyboard(key);
}

void PassiveMotionHandler(int x, int y)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnMouse(0, 0, x, y);

    PassiveMouseComponentsHandler(x, y);
}

void GameMouseHandler(int button, int state, int x, int y)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnMouse(button, state, x, y);
}

void PassiveMouseComponentsHandler(int x, int y)
{
    y = ClientHeight - y;
    for (int i = 0; i < ComponentsList.size(); i++)
    {
        ComponentsList[i]->SetHover(x, y);
        if (ComponentsList[i]->isHover())
            std::cout << "Panel " << i << " is hovered!\n";
    }
}

void SetMenuComponents()
{
    ComponentsList.clear();

    ComponentsList.push_back(std::make_unique<rgl::Panel>());
    ComponentsList[0]->SetRect(0, 0, 1920, 1080);
    ComponentsList[0]->SetColor(Vector4f(0.024, 0.471, 0.922, 1.0f));
    ComponentsList.push_back(std::make_unique<rgl::PlayButton>(Font));
    ComponentsList.push_back(std::make_unique<rgl::SettingsButton>(Font));
    ComponentsList.push_back(std::make_unique<rgl::ExitButton>(Font));
}

void GameKernelInit()
{
    LoadMeshes();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //ActiveScenario = std::make_unique<Scenario>("../contents/scenarios/map2.txt");
    //ActiveScenario->DrawSubsystemInit();
}

void GameInterfaceInit()
{
    InterfaceShader = new InterfaceTechnique;
    InterfaceShader->Init();

    Font = std::make_shared<rgl::FontRenderer>();
    Font->InitFontRenderer(ClientWidth, ClientHeight);

    //ComponentsList.push_back(std::make_unique<rgl::UpperPanel>());
    //ComponentsList.push_back(std::make_unique<rgl::LowerPanel>());

    SetMenuComponents();

    //ComponentsList.push_back(std::make_unique<rgl::Label>(100, 100, Font));
    //ComponentsList.push_back(std::make_unique<rgl::Label>(100, 200, Font));
    //ComponentsList.push_back(std::make_unique<rgl::Label>(100, 300, Font));
}

void GameFrame()
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnFrame();
}

void UpdateGameWindowSize(int width, int height)
{
    if (ActiveScenario)
    {
        ActiveScenario->ProjectionInfo.Width = (float)ClientWidth;
        ActiveScenario->ProjectionInfo.Height = (float)ClientHeight;
        ActiveScenario->GameCamera.SetWindowSize(ClientWidth, ClientHeight);
    }
}

void DrawInterface()
{
    InterfaceShader->Enable();

    for (int i = 0; i < ComponentsList.size(); i++)
    {
        ComponentsList[i]->Render(*InterfaceShader);
    }

    Font->RenderText(rgl::FONT_TYPE_OLD_STANDARD_30, rgl::clOrange1, rgl::clYellow, 50, 1000, "They are Gigabytes!");
}

void DrawGameFrame()
{
    if (ActiveScenario)
        ActiveScenario->DrawGameFrame();
}
