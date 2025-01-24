#include "game_kernel.hpp"

#include <glew.h>   // Should be before GLFW even if I dont use glew.
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <memory>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include "interface.hpp"
#include "math_3d.h"
#include "shaders.hpp"
#include "interface_technique.hpp"
#include "meshes_manager.hpp"
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

void LaunchScenario(std::string scenario_name);

int ClientWidth = 1920;
int ClientHeight = 1080;

std::shared_ptr<rgl::FontRenderer> Font;
std::unique_ptr<Scenario> ActiveScenario;

InterfaceTechnique* InterfaceShader;
GUI::MainMenuState MenuState;


void GameKeyboardHandler(int key)
{
    if (ActiveScenario)
        ActiveScenario->GameCamera.OnKeyboard(key);

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        ActiveScenario = nullptr;
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
}

void LaunchScenario(std::string scenario_name)
{
    ActiveScenario = std::make_unique<Scenario>(scenario_name);
    ActiveScenario->DrawSubsystemInit();
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
}

void GameInterfaceInit()
{
    InterfaceShader = new InterfaceTechnique;
    InterfaceShader->Init();

    Font = std::make_shared<rgl::FontRenderer>();
    Font->InitFontRenderer(ClientWidth, ClientHeight);

    MenuState.isActiveScenario = false;
    MenuState.scenarioName = "contents/scenarios/map.txt";
}

void GameFrame()
{
    if (MenuState.isActiveScenario == true) {
        LaunchScenario(MenuState.scenarioName);
        MenuState.isActiveScenario = false;
    }
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
    //InterfaceShader->Enable();
    if (!ActiveScenario) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Font->RenderText(rgl::FONT_TYPE_OLD_STANDARD_30, rgl::clOrange1, rgl::clYellow, 50, 1000, "They are Gigabytes!");
        GUI::DrawMainMenu(MenuState);
    }
}

void DrawGameFrame()
{
    if (ActiveScenario)
        ActiveScenario->DrawGameFrame();
}
