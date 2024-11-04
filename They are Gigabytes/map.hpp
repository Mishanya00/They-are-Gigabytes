#pragma once

#include "basic_mesh.hpp"
#include "basic_model.hpp"
#include "lighting_technique.hpp"
#include <vector>
#include <memory>

/*
class Drawable
{
public:
	Drawable() {}
	virtual void Render() = 0;
}; */

enum TyleType
{
	ttEnergy,
	ttNormal
};

struct Tile
{
	TyleType type;
	bool isWalkable;
	std::unique_ptr<BasicModel> model;
};

class Map
{
public:

	Map();
	Map(int width, int height);
	~Map();

	bool Init();
	void Render(LightingTechnique & shader, DirectionalLight & light);


private:
	int width_, height_;
	std::vector<std::vector<Tile>> tiles_;
	std::shared_ptr<BasicMesh> tile_mesh_;
};
