#include "map.hpp"

#include "world_transform.hpp"
#include <glew.h>

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

	if (!tile_mesh_->LoadMesh("../contents/tile/map_tile.obj")) {
		return false;
	}
	return true;
}

void Map::Render(FirstTechnique & gWorld)
{
	rgl::WorldTransform TileMatrix;
	TileMatrix.SetScale(1.0f);
	TileMatrix.SetRotation(Vector3f(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			TileMatrix.SetPosition(Vector3f(static_cast<float>(2*j), 0.0f, static_cast<float>(2*i)));
			gWorld.SetWorldUniform(TileMatrix.GetMatrix());
			//glUniformMatrix4fv(gWorld, 1, GL_TRUE, &TileMatrix.GetMatrix().m[0][0]);

			tile_mesh_->Render();
		}
	}

}