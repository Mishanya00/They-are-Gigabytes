#pragma once

#include <string>
#include <vector>
#include <glew.h>
#include "math_3d.h"
#include "interface_technique.hpp"

namespace rgl
{
	class Panel
	{
	public:

		//Panel() {}
		Panel(float left, float bottom, float right, float top);

		void Render(InterfaceTechnique& shader);

		void SetHover(int mouseX, int mouseY);
		void SetColor(Vector3f new_color);

		bool isHover();
		bool isVisible();
		virtual void Click();
		

	protected:

		GLuint VBO_;
		int left_, bottom_, right_, top_;
		Vector3f vertices_[6];
		Vector3f color_;
		char isHover_, isDown_, isVisible_;
	};

	class UpperPanel : public Panel
	{
	public:
		UpperPanel(float left, float bottom, float right, float top);
		
		void Click();
	};

	class Label
	{};
}