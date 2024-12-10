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
		model_ = std::make_unique<BasicModel>(tower_mesh, 4.0f, 0, 4.0f);
		model_->SetScale(1.1f);
		break;
	case btZiggurat:
		model_ = std::make_unique<BasicModel>(zigg_mesh, 4.0f, 0, 4.0f);
		model_->SetScale(2.0f);
		break;
	case btCPU:
		model_ = std::make_unique<BasicModel>(cpu_mesh, 4.0f, 0, 4.0f);
		model_->SetScale(1.7f);
		break;
	default:
		return;
	}

	model_->SetCoords(position.x, position.y, position.z);
}

void Building::Render(LightingTechnique& shader, DirectionalLight& light)
{
	model_->Render(shader, light);
}