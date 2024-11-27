#include "game_kernel.hpp"

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
#include "basic_model.hpp"

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

std::shared_ptr<BasicMesh> tower_mesh;
std::shared_ptr<BasicMesh> zigg_mesh;
std::unique_ptr<BasicModel> tower;
std::unique_ptr<BasicModel> zigg;


void LoadMeshes()
{
    tower_mesh = std::make_shared<BasicMesh>();
    if (!tower_mesh->LoadMesh("../contents/buildings/tower/tower2.obj")) {
        std::cerr << "Tower mesh not loaded!\n";
    }
    zigg_mesh = std::make_shared<BasicMesh>();
    if (!zigg_mesh->LoadMesh("../contents/buildings/ziggurat/p3.obj")) {
        std::cerr << "Ziggurat mesh not loaded!\n";
    }
}


void GameKernelInit()
{
    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.2f);
    GameCamera.SetRotationSpeed(1.5f);
    GameCamera.Rotate(45.0f, 0, 0);

    Field = new Map(10, 10);
    Field->Init();
    LoadMeshes();
}

void DrawSubsystemInit()
{
    WorldMatrix.SetScale(1.0f);
    WorldMatrix.SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
    WorldMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

    GlobalLight.AmbientIntensity = 0.2f;
    GlobalLight.DiffuseIntensity = 1.0f;
    GlobalLight.Color = Vector3f(1.0f, 1.0f, 1.2f);
    GlobalLight.WorldDirection = Vector3f(0.5f, -1.0f, 0.5f);

    tower = std::make_unique<BasicModel>(tower_mesh, 4.0f, 0, 4.0f);
    tower->SetCoords(8.0f, 0, 16.0f);
    tower->SetScale(1.1f);
    zigg = std::make_unique<BasicModel>(zigg_mesh, 4.0f, 0, 4.0f);
    zigg->SetCoords(10.0f, 0, 16.0f);
    zigg->SetScale(1.1f);

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
    //glBlendFunc(GL_SRC_ALPHA, 

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    glOrtho(0, 1920, 1080, 0, 1, -1);
}

void GameFrame()
{
    GameCamera.OnFrame();
    
    static float temp_speed = -0.01;
    tower->Move(0, 0, temp_speed);
    if (tower->GetPosition().z < 0)
        temp_speed = 0.01;
    if (tower->GetPosition().z > 100.0)
        temp_speed = -0.01;
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

    rgl::Panel bottom_panel(0.0f, 0.0f, 1920.0f, 200.0f);
    bottom_panel.Render(*InterfaceShader);
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
    tower->Render(*ActiveShader, GlobalLight);
    zigg->Render(*ActiveShader, GlobalLight);
}
