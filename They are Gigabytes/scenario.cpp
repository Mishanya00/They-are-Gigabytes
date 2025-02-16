#include "scenario.hpp"

#include <glew.h>
#include <sstream>
#include "scenario_interface.hpp"


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

    GUI::InitGameState();
    ReadScenarioInfo();
}

void Scenario::DrawSubsystemInit()
{
    GlobalLight.AmbientIntensity = 0.3f;
    GlobalLight.DiffuseIntensity = 1.0f;
    GlobalLight.Color = Vector3f(0.9f, 0.9f, 1.0f);
    GlobalLight.WorldDirection = Vector3f(0.5f, -1.0f, 0.5f);

    LightingShader = std::make_unique<LightingTechnique>();
    LightingShader->Init();
}

void Scenario::DrawGameFrame()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    LightingShader->Enable();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //GameCamera.OnRender();

    Matrix4f ProjectionMatrix;
    ProjectionMatrix.InitPersProjTransform(ProjectionInfo);

    Matrix4f ViewMatrix = GameCamera.GetMatrix();

    LightingShader->SetRenderMode(lsrmClassic);
    LightingShader->SetWorldUniform(WorldMatrix.GetMatrix());
    LightingShader->SetProjectionUniform(ProjectionMatrix);
    LightingShader->SetViewUniform(ViewMatrix);

    LightingShader->SetEffectStatus(lseColorGrading, GUI::GameState.isColorGradingEffect);
    LightingShader->SetEffectStatus(lseNoise, GUI::GameState.isNoiseEffect);

    Field->Render(*LightingShader, GlobalLight);

    for (int i = 0; i < BuildingsList.size(); i++)
    {
        if (GUI::GameState.isInvisibleEffect) {
            LightingShader->SetEffectStatus(lseVignette, 1);
        }
        else { LightingShader->SetEffectStatus(lseVignette, 0); }

        if (GUI::GameState.isSelectedEffect) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            LightingShader->SetRenderMode(lsrmSelected);
            BuildingsList[i]->Render(*LightingShader, GlobalLight);
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        LightingShader->SetRenderMode(lsrmClassic);
        BuildingsList[i]->Render(*LightingShader, GlobalLight);
    }
    LightingShader->SetEffectStatus(lseVignette, 0);
}