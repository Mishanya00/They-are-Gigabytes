#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace rgl
{

	Texture::Texture(GLenum texture_type, const std::string& file_name)
	{
		texture_target_ = texture_type;
		file_name_ = file_name;
	}
	bool Texture::Load()
	{
		stbi_set_flip_vertically_on_load(1);

		unsigned char* pImage_data = stbi_load(file_name_.c_str(), &image_width_, &image_height_, &image_bit_per_pixel_, 0);
		if (!pImage_data) {
			std::cerr << "Can't load texture from '" << file_name_.c_str() << "' - " << stbi_failure_reason() << '\n';
			return false;
		}

		std::cout << "Width: " << image_width_ << " Height: " << image_height_ << " bits per pixel: " << image_bit_per_pixel_ << '\n';

		glGenTextures(1, &textureID_);
		glBindTexture(texture_target_, textureID_);

		if (texture_target_ != GL_TEXTURE_2D)
		{
			std::cout << "Support for texture target " << texture_target_ << " is not implemented yet!\n";
			return false;
		}

		glTexParameterf(texture_target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(texture_target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(texture_target_, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(texture_target_, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(texture_target_, 0, GL_RGB, image_width_, image_height_, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage_data);

		glBindTexture(texture_target_, 0);

		stbi_image_free(pImage_data);

		return true;
	}

	void Texture::Bind(GLenum texture_unit)
	{
		glActiveTexture(texture_unit);
		glBindTexture(texture_target_, textureID_);
	}
}