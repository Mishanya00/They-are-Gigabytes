#include "building.hpp"

Building::Building(BuildingType type, int max_hp, int hp)
{
	type_ = type;
	max_hp_ = max_hp;
	hp_ = hp;

	switch (type_)
	{
	case btShieldTower:

		break;
	case btZiggurat:
		break;
	}
}