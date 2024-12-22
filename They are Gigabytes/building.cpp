#include "building.hpp"
#include "meshes_manager.hpp"


Building::Building(BuildingType type, Vector3f position, int max_hp, int hp)
{
	type_ = type;
	max_hp_ = max_hp;
	hp_ = hp;


	switch (type_)
	{
	case btShieldTower:
		model_ = std::make_unique<BasicModel>(tower_mesh, position);
		model_->SetScale(1.1f);
		break;
	case btZiggurat:
		model_ = std::make_unique<BasicModel>(zigg_mesh, position);
		model_->SetScale(2.0f);
		break;
	case btCPU:
		model_ = std::make_unique<BasicModel>(cpu_mesh, position);
		model_->SetScale(2.0f);
		break;
	case btEnergyExtractor:
		model_ = std::make_unique<BasicModel>(extractor_mesh, position.x, position.y, position.z+0.2);
		model_->SetScale(0.35f);
		break;
	case btScience:
		model_ = std::make_unique<BasicModel>(science_mesh, position);
		model_->SetScale(0.35f);
		break;
	case btAntivirus:
		model_ = std::make_unique<BasicModel>(antivirus_mesh, position);
		model_->SetScale(0.25f);
		break;
	default:
		return;
	}
}

void Building::Render(LightingTechnique& shader, DirectionalLight& light)
{
	model_->Render(shader, light);
}