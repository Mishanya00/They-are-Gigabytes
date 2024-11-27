#pragma once

#include <string>
#include <glew.h>
#include "math_3d.h"
#include "interface_technique.hpp"

namespace rgl
{
	class Panel
	{
	public:

		Panel(float left, float bottom, float right, float top);

		void Render(InterfaceTechnique& shader);
		bool isHover();
		bool isVisible();

	private:

		GLuint VBO_;
		Vector3f vertices_[6];
		Vector3f color_;
		char isHover_, isDown_, isVisible_;
	};

	class Button
	{
		std::string name;
		std::string caption;

		float vert[8];
		char isHover, isDown;
		int checkGroup, radioGroup;
		// text
		//float buffer[50 * nameLen];
		int num_quads;
		float textPosX, textPosY, textScale;
	};

	class Label
	{};
}
