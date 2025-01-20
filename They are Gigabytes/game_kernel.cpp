#include "game_kernel.hpp"

#include <glew.h>   // Should be before GLFW even if I dont use glew.
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <memory>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include "math_3d.h"

#include "shaders.hpp"
#include "interface_technique.hpp"

#include "meshes_manager.hpp"

#include "panels.hpp"
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
void SetMenuComponents();

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
        ActiveScenario = nullptr;
        SetMenuComponents();
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
    if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
    {
        for (int i = 0; i < ComponentsList.size(); ++i)
        {
            if (ComponentsList[i]->isHover())
            {
                switch (ComponentsList[i]->GetComponentType())
                {
                case rgl::ctButtonPlay:
                    std::cout << "Play btn pressed!\n";

                    if (!ActiveScenario)
                    {
                        LoadMeshes();
                        LaunchScenario("contents/scenarios/map_all.txt");
                    }
                    break;
                case rgl::ctButtonSettings:
                    std::cout << "Settings btn pressed!\n";
                    break;
                case rgl::ctButtonExit:
                    std::cout << "Exit btn pressed!\n";
                    exit(0);
                    break;
                }
            }
        }
    }
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
    }
}

void SetMenuComponents()
{
    ComponentsList.clear();

    ComponentsList.push_back(std::make_unique<rgl::Panel>());
    ComponentsList[0]->SetRect(0, 0, 1920, 1080);
    ComponentsList[0]->SetColor(Vector4f(0.051, 0.157, 0.62, 1.0f));

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[1]->SetRect(500, 700, 1500, 800);
    ComponentsList[1]->SetText("PLAY!");
    ComponentsList[1]->SetComponentType(rgl::ctButtonPlay);

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[2]->SetRect(500, 500, 1500, 600);
    ComponentsList[2]->SetText("SETTINGS!");
    ComponentsList[2]->SetComponentType(rgl::ctButtonSettings);

    ComponentsList.push_back(std::make_unique<rgl::TextPanel>(Font));
    ComponentsList[3]->SetRect(500, 300, 1500, 400);
    ComponentsList[3]->SetText("Exit!");
    ComponentsList[3]->SetComponentType(rgl::ctButtonExit);
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

    SetMenuComponents();
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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Main menu");
    ImGui::Text("Will it work?");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DrawGameFrame()
{
    if (ActiveScenario)
        ActiveScenario->DrawGameFrame();
}
