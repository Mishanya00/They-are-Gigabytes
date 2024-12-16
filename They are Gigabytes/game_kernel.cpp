#include "game_kernel.hpp"

#include <glfw3.h>
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


void GameKeyboardHandler(int key)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnKeyboard(key);

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        exit(0);
        break;
    }
}

void GameKeyboardSpecialHandler(int key, int x, int y)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnKeyboard(key);
}

void GamePassiveMotionHandler(int x, int y)
{
    std::cout << x << ' ' << y << '\n';
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnMouse(x, y);

    PassiveMouseComponentsHandler(x, y);
}

void GameMouseHandler(int button, int state, int x, int y)
{
}

void GameMouseScrollHandler(double yoffset)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnScroll(yoffset);
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
    ComponentsList[0]->SetColor(Vector4f(0.051, 0.157, 0.62, 1.0f));
    ComponentsList[0]->SetComponentType(rgl::ctButtonPlay);

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[1]->SetRect(500, 700, 1500, 800);
    ComponentsList[1]->SetText("PLAY!");
    ComponentsList[1]->SetComponentType(rgl::ctButtonPlay);

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[2]->SetRect(500, 500, 1500, 600);
    ComponentsList[2]->SetText("SETTINGS!");
    ComponentsList[2]->SetComponentType(rgl::ctButtonPlay);

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[3]->SetRect(500, 300, 1500, 400);
    ComponentsList[3]->SetText("Exit!");
    ComponentsList[3]->SetComponentType(rgl::ctButtonPlay);
}

void SetGameComponents()
{
    ComponentsList.clear();

    ComponentsList.push_back(std::make_unique<rgl::UpperPanel>());
    ComponentsList.push_back(std::make_unique<rgl::LowerPanel>());
}

void LaunchScenario(std::string scenario_name)
{
    ActiveScenario = std::make_unique<Scenario>(scenario_name);
    ActiveScenario->DrawSubsystemInit();
    SetGameComponents();
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
    LaunchScenario("contents/scenarios/map.txt");
}

void GameInterfaceInit()
{
    InterfaceShader = new InterfaceTechnique;
    InterfaceShader->Init();

    Font = std::make_shared<rgl::FontRenderer>();
    Font->InitFontRenderer(ClientWidth, ClientHeight);

    //SetMenuComponents();
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
