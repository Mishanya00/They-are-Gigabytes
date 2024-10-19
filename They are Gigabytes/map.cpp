#include "map.hpp"

#include "world_transform.hpp"

Map::Map()
{
	width_ = 10;
	height_ = 10;
	Init();
}

Map::Map(int width, int height)
{
	width_ = width;
	height_ = height;
	Init();
}

Map::~Map()
{
	if (tile_mesh_)
		delete tile_mesh_;
}

bool Map::Init()
{
	tile_mesh_ = new BasicMesh();
	tiles_.resize(height_);

	for (int i = 0; i < height_; i++)
	{
		tiles_[i].resize(width_);
		for (int j = 0; j < width_; j++)
		{
			tiles_[i][j].isWalkable = true;
			tiles_[i][j].type = ttNormal;
		}
	}

	if (!tile_mesh_->LoadMesh("../contents/map_tile.obj")) {
		return false;
	}
	return true;
}

void Map::Render()
{
	tile_mesh_->Render();
}