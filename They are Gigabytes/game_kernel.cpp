#include "game_kernel.hpp"
#include "map.hpp"
#include <iostream>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"
#include "shaders.hpp"
#include "first_technique.hpp"
#include "basic_mesh.hpp"


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
BasicMesh* tower;


void GameKernelInit()
{
    WorldMatrix.SetScale(1.0f);
    WorldMatrix.SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
    WorldMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.1f);
    GameCamera.SetRotationSpeed(1.0f);
    GameCamera.Rotate(45.0f, 0, 0);

    ActiveShader = new FirstTechnique;
    ActiveShader->Init();
    ActiveShader->Enable();

    Field = new Map(10, 10);
    Field->Init();
}

void DrawSubsystemInit()
{
    tower = new BasicMesh();
    if (!tower->LoadMesh("../contents/buildings/kernel/kernel.obj")) {
        std::cerr << "Tower mesh not loaded!\n";
    }

    //pTexture = new rgl::Texture(GL_TEXTURE_2D, "../contents/tile/tile_texture.jpg");
    pTexture = new rgl::Texture(GL_TEXTURE_2D, "../contents/tex.jpg");
    if (!pTexture->Load())
    {
        std::cerr << "Texture not loaded\n";
        exit(1);
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
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

    //Texture
    pTexture->Bind(GL_TEXTURE0);
    //glUniform1i(gSamplerLocation, 0);
    ActiveShader->SetTextureUnit(0);
    tower->Render();
    Field->Render(*ActiveShader);
    tower->Render();
    
}