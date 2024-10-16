#pragma once

#include <string>
#include <glew.h>


#define COLOR_TEXTURE_UNIT              GL_TEXTURE0


namespace rgl
{
	class Texture
	{
	public:

		Texture(GLenum texture_type, const std::string& file_name);

		bool Load();
		
		void Bind(GLenum texture_unit);

	private:

		std::string file_name_;
		GLenum texture_target_;
		GLuint textureID_;

		int image_width_, image_height_, image_bit_per_pixel_;
	};
}
