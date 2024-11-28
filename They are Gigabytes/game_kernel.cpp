#include "game_kernel.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"

#include "shaders.hpp"
#include "first_technique.hpp"
#include "lighting_technique.hpp"
#include "interface_technique.hpp"

#include "basic_mesh.hpp"
#include "models_manager.hpp"
#include "building.hpp"

#include "map.hpp"

#include "interface.hpp"


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

rgl::Texture* pTexture = NULL;

int ClientWidth = 1920; 
int ClientHeight = 1080;

PersProjInfo ProjectionInfo{ 90.0f, (float)ClientWidth, (float)ClientHeight, 0.1f, 100.0f };
rgl::WorldTransform WorldMatrix;
rgl::Camera GameCamera(ClientWidth, ClientHeight);
Map * Field; // dangerous moment. I cannot call map constructor before compilation because it's dependent of ope
 
LightingTechnique* ActiveShader;
InterfaceTechnique* InterfaceShader;
DirectionalLight GlobalLight;

std::vector<std::unique_ptr <Building>> BuildingsList;


void GameKernelInit()
{
    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.2f);
    GameCamera.SetRotationSpeed(1.5f);
    GameCamera.Rotate(45.0f, 0, 0);

    Field = new Map(10, 10);
    Field->ReadSave("../contents/first_map.txt");
    Field->Init();
}

void DrawSubsystemInit()
{
    LoadMeshes();

    WorldMatrix.SetScale(1.0f);
    WorldMatrix.SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
    WorldMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

    GlobalLight.AmbientIntensity = 0.2f;
    GlobalLight.DiffuseIntensity = 1.0f;
    GlobalLight.Color = Vector3f(1.0f, 1.0f, 1.2f);
    GlobalLight.WorldDirection = Vector3f(0.5f, -1.0f, 0.5f);

    for (int i = 0; i < Field->GetHeight(); i++)
    {
        BuildingsList.push_back(std::make_unique<Building>(btCPU, Vector3f(0.0f, 0.0f, 2*i), 1000, 1000));
        BuildingsList.push_back(std::make_unique<Building>(btShieldTower, Vector3f(2.0f, 0.0f, 2*i), 1000, 1000));
        BuildingsList.push_back(std::make_unique<Building>(btZiggurat, Vector3f(4.0f, 0.0f, 2*i), 1000, 1000));
    }


    ActiveShader = new LightingTechnique;
    ActiveShader->Init();

    InterfaceShader = new InterfaceTechnique;
    InterfaceShader->Init();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    glOrtho(0, 1920, 1080, 0, 1, -1);
}

void GameFrame()
{
    GameCamera.OnFrame();
}

void UpdateGameWindowSize(int width, int height)
{
    ProjectionInfo.Width = (float)ClientWidth;
    ProjectionInfo.Height = (float)ClientHeight;
    GameCamera.SetWindowSize(ClientWidth, ClientHeight);
}

void DrawInterface()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    InterfaceShader->Enable();
    InterfaceShader->SetColorUniform(0.0f, 0.0f, 0.0f, 1.0f);

    rgl::Panel upper_panel(0.0f, 1030.0f, 1920.0f, 1080.0f);
    rgl::Panel bottom_panel(0.0f, 0.0f, 1920.0f, 150.0f);

    bottom_panel.Render(*InterfaceShader);
    upper_panel.Render(*InterfaceShader);
}

void DrawGameFrame()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    ActiveShader->Enable();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameCamera.OnRender();

    Matrix4f ProjectionMatrix;
    ProjectionMatrix.InitPersProjTransform(ProjectionInfo);

    Matrix4f ViewMatrix = GameCamera.GetMatrix();

    ActiveShader->SetWorldUniform(WorldMatrix.GetMatrix());
    ActiveShader->SetProjectionUniform(ProjectionMatrix);
    ActiveShader->SetViewUniform(ViewMatrix);
    
    Field->Render(*ActiveShader, GlobalLight);

    for (int i = 0; i < BuildingsList.size(); i++)
    {
        BuildingsList[i]->Render(*ActiveShader, GlobalLight);
    }
}
