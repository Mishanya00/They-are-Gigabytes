#include "game_kernel.hpp"
#include "map.hpp"
#include <iostream>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"
#include "shaders.hpp"
#include "first_technique.hpp"
#include "basic_mesh.hpp"
#include "basic_model.hpp"
#include <memory>


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
FirstTechnique* ActiveShader;

std::shared_ptr<BasicMesh> tower_mesh;
std::unique_ptr<BasicModel> tower;


void GameKernelInit()
{
    WorldMatrix.SetScale(1.0f);
    WorldMatrix.SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
    WorldMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.2f);
    GameCamera.SetRotationSpeed(1.5f);
    GameCamera.Rotate(45.0f, 0, 0);

    ActiveShader = new FirstTechnique;
    ActiveShader->Init();
    ActiveShader->Enable();

    Field = new Map(50, 50);
    Field->Init();
}

void DrawSubsystemInit()
{
    //tower_mesh = new BasicMesh();
    tower_mesh = std::make_shared<BasicMesh>();
    if (!tower_mesh->LoadMesh("../contents/buildings/ziggurat/p3.obj")) {
        std::cerr << "Tower mesh not loaded!\n";
    }
    tower = std::make_unique<BasicModel>(tower_mesh, 4.0f, 0, 4.0f);
    tower->SetCoords(8.0f, 0, 16.0f);
    tower->SetScale(1.1f);


    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

void GameFrame()
{
    GameCamera.OnFrame();
    tower->Move(0, 0, -0.01);
}

void UpdateGameWindowSize(int width, int height)
{
    ProjectionInfo.Width = (float)ClientWidth;
    ProjectionInfo.Height = (float)ClientHeight;
    GameCamera.SetWindowSize(ClientWidth, ClientHeight);
}

void DrawGameFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameCamera.OnRender();

    Matrix4f ProjectionMatrix;
    ProjectionMatrix.InitPersProjTransform(ProjectionInfo);

    Matrix4f ViewMatrix = GameCamera.GetMatrix();

    ActiveShader->SetWorldUniform(WorldMatrix.GetMatrix());
    ActiveShader->SetProjectionUniform(ProjectionMatrix);
    ActiveShader->SetViewUniform(ViewMatrix);

    ActiveShader->SetTextureUnit(0);

    Field->Render(*ActiveShader);
    tower->Render(*ActiveShader);
}