#pragma once

#include "basic_mesh.hpp"
#include "first_technique.hpp"
#include <vector>


enum TyleType
{
	ttEnergy,
	ttNormal
};

struct Tile
{
	TyleType type;
	bool isWalkable;
};

class Map
{
public:

	Map();
	Map(int width, int height);
	~Map();

	bool Init();
	void Render(FirstTechnique & gWorld);


private:
	int width_, height_;
	std::vector<std::vector<Tile>> tiles_;
	BasicMesh * tile_mesh_;
};
