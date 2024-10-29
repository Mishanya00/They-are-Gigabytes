#pragma once

#include <glew.h>
#include <string>
#include <list>
#include "math_3d.h"

class Technique
{
public:

	Technique();

	virtual ~Technique();

	virtual bool Init();

	void Enable();


	// Here will be all uniform parameters that are needed to transmit to shader program of any class
	// Here they are empty, so neccessary ones will be overrided in classes-descendants
	virtual void SetWorldUniform(const Matrix4f& gWorld) {}
	virtual void SetViewUniform(const Matrix4f& gView) {}
	virtual void SetProjectionUniform(const Matrix4f& gPerspective) {}
	virtual void SetTextureUnit(unsigned int TextureUnit) {}

protected:

	bool AddShader(GLenum shader_type, std::string const& file_name);

	bool Finalize();

	GLint GetUniformLocation(std::string uniform_name);

	GLuint shader_prog_;

private:

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList shader_obj_list_;
};