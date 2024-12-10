#include "game_kernel.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"

#include "shaders.hpp"
#include "first_technique.hpp"
#include "interface_technique.hpp"

#include "models_manager.hpp"

#include "interface.hpp"
#include "freetypeGL.h"

#include "scenario.hpp"


int ClientWidth = 1920;
int ClientHeight = 1080;

std::vector<rgl::Panel> ComponentsList;
rgl::FontRenderer Font;
std::unique_ptr<Scenario> ActiveScenario;

InterfaceTechnique* InterfaceShader;


void KeyboardHandler(unsigned char key, int x, int y)
{
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
    ActiveScenario->GameCamera.OnKeyboard(key);
}

void PassiveMotionHandler(int x, int y)
{
    ActiveScenario->GameCamera.OnMouse(0, 0, x, y);
    PassiveMouseComponentsHandler(x, y);
}

void GameMouseHandler(int button, int state, int x, int y)
{
    ActiveScenario->GameCamera.OnMouse(button, state, x, y);
}

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

void PassiveMouseComponentsHandler(int x, int y)
{
    y = ClientHeight - y;
    for (int i = 0; i < ComponentsList.size(); i++)
    {
        ComponentsList[i].SetHover(x, y);
        if (ComponentsList[i].isHover())
            std::cout << "Panel " << i << " is hovered!\n";
    }
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

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    ActiveScenario = std::make_unique<Scenario>("../contents/first_map.txt");
    ActiveScenario->DrawSubsystemInit();
}

void GameInterfaceInit()
{
    ComponentsList.push_back(rgl::Panel(0.0f, 0.0f, 1920.0f, 150.0f));
    ComponentsList[ComponentsList.size() - 1].SetColor(Vector3f(0.0f, 0.05f, 0.12f));
    ComponentsList.push_back(rgl::UpperPanel(0.0f, 1030.0f, 1920.0f, 1080.0f));
    ComponentsList[ComponentsList.size() - 1].SetColor(Vector3f(0.0f, 0.05f, 0.12f));

    Font.InitFontRenderer(ClientWidth, ClientHeight);

    InterfaceShader = new InterfaceTechnique;
    InterfaceShader->Init();
}

void GameFrame()
{
    ActiveScenario->GameCamera.OnFrame();
}

void UpdateGameWindowSize(int width, int height)
{
    ActiveScenario->ProjectionInfo.Width = (float)ClientWidth;
    ActiveScenario->ProjectionInfo.Height = (float)ClientHeight;
    ActiveScenario->GameCamera.SetWindowSize(ClientWidth, ClientHeight);
}

void DrawInterface()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    InterfaceShader->Enable();

    for (int i = 0; i < ComponentsList.size(); i++)
    {
        ComponentsList[i].Render(*InterfaceShader);
    }

    Font.RenderText(rgl::FONT_TYPE_OLD_STANDARD_30, rgl::clOrange1, rgl::clYellow, 50, 1000, "They are Gigabytes!");
    Font.RenderText(rgl::FONT_TYPE_OLD_STANDARD_46, rgl::clBlue, rgl::clYellow, 50, 900, "They are Gigabytes!");
    Font.RenderText(rgl::FONT_TYPE_SOURCE_CODE_PRO_30, rgl::clYellow, rgl::clYellow, 50, 800, "They are Gigabytes!");
    Font.RenderText(rgl::FONT_TYPE_SOURCE_CODE_PRO_46, rgl::clRed, rgl::clYellow, 50, 700, "They are Gigabytes!");
    Font.RenderText(rgl::FONT_TYPE_SOURCE_SANS_PRO_30, rgl::clCyan, rgl::clYellow, 50, 600, "They are Gigabytes!");
    Font.RenderText(rgl::FONT_TYPE_SOURCE_SANS_PRO_46, rgl::clWhite, rgl::clYellow, 50, 500, "They are Gigabytes!");
}

void DrawGameFrame()
{
    ActiveScenario->DrawGameFrame();
}
