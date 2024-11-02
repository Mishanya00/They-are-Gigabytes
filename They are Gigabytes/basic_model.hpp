#pragma once

#include "basic_mesh.hpp"

#include <memory>
#include <string>

#include "math_3d.h"
#include "technique.hpp"
#include "first_technique.hpp"
#include "lighting_technique.hpp"


class BasicModel
{
public:

	// shared pointer not to duplicate the same meshes for each existing model
	BasicModel(std::shared_ptr<BasicMesh>, Vector3f coords);
	BasicModel(std::shared_ptr<BasicMesh>, float x, float y, float z);


	void Render(FirstTechnique & shader);
	void Render(LightingTechnique& shader);

private:

	std::shared_ptr<BasicMesh> mesh_;
	Vector3f coord_;
	Vector3f tilt_;		// in case someone wants to rotate models
	float scale_;
};