#include "scenario.hpp"

#include <glew.h>


Scenario::Scenario(std::string map_name)
{
    Field = new Map(10, 10);
    Field->ReadSave("../contents/first_map.txt");
    Field->Init();

    ScenarioInit();
}

void Scenario::ScenarioInit()
{
    GameCamera.SetWindowSize(1920, 1080);
    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.2f);
    GameCamera.SetRotationSpeed(1.5f);
    GameCamera.Rotate(45.0f, 0, 0);
}

void Scenario::DrawSubsystemInit()
{
    GlobalLight.AmbientIntensity = 0.2f;
    GlobalLight.DiffuseIntensity = 1.0f;
    GlobalLight.Color = Vector3f(1.0f, 1.0f, 1.2f);
    GlobalLight.WorldDirection = Vector3f(0.5f, -1.0f, 0.5f);

    for (int i = 0; i < Field->GetHeight(); i++)
    {
        BuildingsList.push_back(std::make_unique<Building>(btCPU, Vector3f(0.0f, 0.0f, 2 * i), 1000, 1000));
        BuildingsList.push_back(std::make_unique<Building>(btShieldTower, Vector3f(2.0f, 0.0f, 2 * i), 1000, 1000));
        BuildingsList.push_back(std::make_unique<Building>(btZiggurat, Vector3f(4.0f, 0.0f, 2 * i), 1000, 1000));
    }

    ActiveShader = new LightingTechnique;
    ActiveShader->Init();
}

void Scenario::DrawGameFrame()
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