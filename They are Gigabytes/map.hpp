#pragma once

#include "basic_model.hpp"
#include "lighting_technique.hpp"

#include <string>
#include <vector>
#include <memory>


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

	void ReadSave(std::string save_file);
	bool Init();
	void Render(LightingTechnique& shader, DirectionalLight & light);

	int GetWidth() { return width_;  }
	int GetHeight() { return height_; }

private:
	int width_, height_;
	std::vector<std::vector<Tile>> tiles_;
};
