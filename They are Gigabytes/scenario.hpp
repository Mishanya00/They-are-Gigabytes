#pragma once

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

#include "world_transform.hpp"
#include "camera.hpp"


class Scenario
{
public:
	Scenario(std::string map_name);
	
	void ScenarioInit();
	void DrawSubsystemInit();
	void DrawGameFrame();


	rgl::Camera GameCamera;
	PersProjInfo ProjectionInfo{ 90.0f, (float)ClientWidth, (float)ClientHeight, 0.1f, 100.0f };

private:
	std::vector<std::unique_ptr <Building>> BuildingsList;
	rgl::WorldTransform WorldMatrix;
	Map* Field;

	LightingTechnique* ActiveShader;
	DirectionalLight GlobalLight;
};