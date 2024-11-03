#pragma once

#include <memory>
#include "basic_model.hpp"


enum BuildingType {
	btKernel,
	btShieldTower,
	btCPU,
	btAntivirus,
	btScaner,
	btPointDefense,
	btEnergyStorage,
	btEnergyExtractor,
	btZiggurat,
};

class Building
{
public:



private:

	BuildingType type_;
	std::unique_ptr<BasicModel> model_;
	int max_hp_, hp_;
};
