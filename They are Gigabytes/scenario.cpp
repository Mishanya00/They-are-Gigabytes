#include "scenario.hpp"

#include <glew.h>
#include <sstream>


Scenario::Scenario(std::string map_name)
{
    scenario_name_ = map_name;
    Field = std::make_unique<Map>();
    Field->ReadSave(scenario_name_);

    ScenarioInit();
}

void Scenario::ReadScenarioInfo()
{
    std::string buffer;
    std::stringstream ss;
    int x, y;
    int curr_element;

    mishanya::ReadFile(scenario_name_, buffer);
    ss << buffer;

    ss >> y >> x;

    // One file for map and for all objects on it, so initially we skip to the buildings part
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            ss >> curr_element;
        }
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            ss >> curr_element;
            if (curr_element >= btZiggurat && curr_element <= btScience && curr_element != 0)
                BuildingsList.push_back(std::make_unique<Building>(static_cast<BuildingType>(curr_element),
                    Vector3f(static_cast<float>(2 * j), 0.0f, static_cast<float>(2 * i)), 1000, 1000));
        }
    }
}

void Scenario::ScenarioInit()
{
    GameCamera.SetWindowSize(1920, 1080);
    GameCamera.SetPosition(Vector3f(0.0f, 3.0f, -5.0f));
    GameCamera.SetSpeed(0.1f);
    GameCamera.SetRotationSpeed(0.75f);
    GameCamera.Rotate(45.0f, 0, 0);

    ReadScenarioInfo();
}

void Scenario::DrawSubsystemInit()
{
    GlobalLight.AmbientIntensity = 0.2f;
    GlobalLight.DiffuseIntensity = 1.0f;
    GlobalLight.Color = Vector3f(1.0f, 1.0f, 1.2f);
    GlobalLight.WorldDirection = Vector3f(0.5f, -1.0f, 0.5f);

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