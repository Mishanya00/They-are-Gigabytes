#pragma once

#include <vector>
#include <memory>

#include "lighting_technique.hpp"

#include "building.hpp"

#include "map.hpp"

#include "world_transform.hpp"
#include "camera.hpp"


#include <memory>

class Scenario
{
public:
	Scenario(std::string map_name);
	
	void ScenarioInit();
	void DrawSubsystemInit();
	void DrawGameFrame();

	rgl::Camera GameCamera;
	PersProjInfo ProjectionInfo{ 90.0f, (float)1920, (float)1080, 0.1f, 100.0f };

private:

	void ReadScenarioInfo();

	std::string scenario_name_;

	std::vector<std::unique_ptr <Building>> BuildingsList;
	std::unique_ptr<Map> Field;
	
	rgl::WorldTransform WorldMatrix;
	std::unique_ptr<LightingTechnique> LightingShader;
	DirectionalLight GlobalLight;
};