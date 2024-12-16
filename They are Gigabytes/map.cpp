#include "map.hpp"

#include "world_transform.hpp"
#include "mishanya_utils.hpp"
#include "meshes_manager.hpp"
#include <glew.h>
#include <iostream>
#include <sstream>

#define TILE_MODEL_PATH "contents/buildings/tile/tile.obj"


Map::Map()
{
	width_ = 10;
	height_ = 10;
}

Map::Map(int width, int height)
{
	width_ = width;
	height_ = height;
}

Map::~Map() {}

void Map::ReadSave(std::string save_file)
{
	std::string buffer;
	std::stringstream ss;
	int curr_tile;

	mishanya::ReadFile(save_file, buffer);
	ss << buffer;

	ss >> height_ >> width_;
	tiles_.resize(height_);

	for (int i = 0; i < height_; i++)
	{
		tiles_[i].resize(width_);
		for (int j = 0; j < width_; j++)
		{	
			ss >> curr_tile;
			if (curr_tile == 2)
			{
				tiles_[i][j].type = ttEnergy;
				tiles_[i][j].model = std::make_unique<BasicModel>(energy_tile_mesh, static_cast<float>(2 * j), 0.0f, static_cast<float>(2 * i));
			}
			else
			{
				tiles_[i][j].type = ttNormal;
				tiles_[i][j].model = std::make_unique<BasicModel>(tile_mesh, static_cast<float>(2 * j), 0.0f, static_cast<float>(2 * i));
			}

			tiles_[i][j].isWalkable = true;
			tiles_[i][j].model->SetScale(1.01f);	// Initially models were created a little smaller that should be. This line to avoid artefacts
		}
	}
	
}

void Map::Render(LightingTechnique& shader, DirectionalLight& light)
{
	rgl::WorldTransform TileMatrix;
	TileMatrix.SetScale(1.0f);
	TileMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			tiles_[i][j].model->Render(shader, light);
		}
	}
}