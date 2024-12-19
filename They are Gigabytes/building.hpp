#pragma once

#include <memory>
#include "basic_model.hpp"
#include "lighting_technique.hpp"


enum BuildingType {
	btKernel = 1,
	btShieldTower = 2,
	btEnergyExtractor = 3,
	btEnergyStorage = 4,
	btCPU = 5,
	btAntivirus = 6,
	btScaner = 7,
	btPointDefense = 8,
	btScience = 9,
	btZiggurat = -1,
};

class Building
{
public:

	Building(BuildingType type, Vector3f position, int max_hp, int hp);
	void Render(LightingTechnique & shader, DirectionalLight & light);

private:

	BuildingType type_;
	std::unique_ptr<BasicModel> model_;
	int max_hp_, hp_;
};
