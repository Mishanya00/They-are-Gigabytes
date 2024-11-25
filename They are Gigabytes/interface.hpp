#pragma once

#include <string>


namespace rgl
{
	class Panel
	{
		float vert[8];
		char isHover, isDown;

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
