#pragma once

#include <string>
#include <vector>
#include <memory>
#include "math_3d.h"
#include "interface_technique.hpp"
#include "freetypeGL.h"

namespace rgl
{
	class Selection
	{
	public:

		Selection();
		void Render(InterfaceTechnique& shader);
		void SetColor(Vector3f color);

	private:
		
		GLuint VBO_;
		Vector3f color_;
		bool isVisible_;
		float left_, right_, bottom_, top_;
		Vector3f vertices_[6];
	};

	class Panel
	{
	public:
		Panel();

		virtual void Render(InterfaceTechnique& shader);

		void SetRect(int left, int bottom, int right, int top);
		void SetHover(int mouseX, int mouseY);
		void SetColor(Vector4f new_color);

		bool isHover();
		bool isVisible();
		virtual void Click();

	protected:
		GLuint VBO_;
		int left_, bottom_, right_, top_;
		Vector3f vertices_[6];
		Vector4f color_;
		char isHover_, isDown_, isVisible_;
	};

	class UpperPanel : public Panel
	{
	public:
		UpperPanel();

		void Click();
	};

	class LowerPanel : public Panel
	{
	public:
		LowerPanel();

		void Click();
	};

	class Label1 : public Panel
	{
	public:
		Label1(std::shared_ptr<FontRenderer> font);

		void Render(InterfaceTechnique& shader) override;
		//void Click();
	private:
		std::shared_ptr<FontRenderer> font_;
	};
	/*
	class TextPanel : public Panel
	{
	public:
		TextPanel(std::shared_ptr<rgl::FontRenderer> font_renderer, int xCoord, int yCoord);
		TextPanel(std::shared_ptr<rgl::FontRenderer>, std::string label_text, int xCoord, int yCoord);

		//void Render();
		void Render(rgl::FONT_TYPE type);

		// Public for direct changes from code such as in Visual Components Libs
		std::string text;
		vec4 color;
		int x, y;
		bool isVisible;

	private:
		std::shared_ptr<FontRenderer> font_;
	};
	*/
}