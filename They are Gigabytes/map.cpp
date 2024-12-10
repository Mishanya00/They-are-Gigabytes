#include "map.hpp"

#include "world_transform.hpp"
#include "mishanya_utils.hpp"
#include "models_manager.hpp"
#include <glew.h>
#include <iostream>
#include <sstream>

#define TILE_MODEL_PATH "../contents/buildings/tile/tile.obj"


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
	/* Disabled because I use smart pointers
	if (tile_mesh_)
		delete tile_mesh_; */
}

bool Map::Init()
{
	tiles_.resize(height_);

	for (int i = 0; i < height_; i++)
	{
		tiles_[i].resize(width_);
		for (int j = 0; j < width_; j++)
		{
			tiles_[i][j].isWalkable = true;
			tiles_[i][j].type = ttNormal;
			tiles_[i][j].model = std::make_unique<BasicModel>(tile_mesh, static_cast<float>(2 * j), 0.0f, static_cast<float>(2 * i));
		}
	}

	return true;
}

void Map::ReadSave(std::string save_file)
{
	std::string buffer, buffer2;
	std::stringstream ss;

	mishanya::ReadFile(save_file, buffer);
	ss << buffer;

	int x, y;
	ss >> x >> y;
	/*
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{

		}
	}
	*/
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