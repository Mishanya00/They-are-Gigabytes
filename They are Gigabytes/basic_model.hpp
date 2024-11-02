#pragma once

#include "basic_mesh.hpp"

#include <memory>
#include <string>

#include "math_3d.h"
#include "technique.hpp"
#include "first_technique.hpp"
#include "lighting_technique.hpp"
//#include "world_transform.hpp"


class BasicModel
{
public:

	// shared pointer not to duplicate the same meshes for each existing model
	BasicModel(std::shared_ptr<BasicMesh> mesh, Vector3f coords);
	BasicModel(std::shared_ptr<BasicMesh> mesh, float x, float y, float z);


	void Render(FirstTechnique & shader);
	void Render(LightingTechnique& shader);

private:

	//rgl::WorldTransform model_matrix;
	std::shared_ptr<BasicMesh> mesh_;
	Vector3f coords_;
	Vector3f tilt_;		// in case someone wants to rotate models
	float scale_;
};