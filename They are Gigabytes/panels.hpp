#pragma once

#include <string>
#include <vector>
#include <memory>
#include "math_3d.h"
#include "interface_technique.hpp"
#include "freetypeGL.h"

namespace rgl
{
	enum PanelType {
		ctNone,
		ctButtonPlay,
		ctButtonSettings,
		ctButtonExit
	};

	class Panel
	{
	public:
		Panel();

		virtual void Render(InterfaceTechnique& shader);

		void SetRect(int left, int bottom, int right, int top);
		void SetHover(int mouseX, int mouseY);
		void SetColor(Vector4f new_color);
		void SetComponentType(PanelType new_type);

		PanelType GetComponentType();

		bool isHover();
		bool isVisible();
		virtual void Click();

		// for polymorphism (TextPanel). Panel class does not use this functionality
		virtual void SetText(std::string new_text) {}
		virtual void SetFontType(FONT_TYPE new_font_type) {}

	protected:
		PanelType type_ = ctNone;
		GLuint VBO_;
		int left_, bottom_, right_, top_;
		Vector3f vertices_[6];
		vec4 color_;
		char isHover_ = false, isDown_ = false, isVisible_ = true;
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

	class Label : public Panel
	{
	public:
		Label(int xCoord, int yCoord, std::shared_ptr<FontRenderer> font);

		void Render(InterfaceTechnique& shader) override;
		//void Click();

	private:
		std::shared_ptr<FontRenderer> font_;
	};

	// MAIN MENU BUTTONS

	class TextPanel : public Panel
	{
	public:
		TextPanel(std::shared_ptr<FontRenderer> font);

		void SetText(std::string new_text);
		void SetFontType(FONT_TYPE new_font_type);

		void Render(InterfaceTechnique& shader) override;
	private:
		std::string text_;
		FONT_TYPE font_type_;
		std::shared_ptr<FontRenderer> font_;
	};
}