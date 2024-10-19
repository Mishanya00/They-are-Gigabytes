#pragma once

#include <glew.h>
#include <string>
#include <list>

class Technique
{
public:

	Technique();

	virtual ~Technique();

	virtual bool Init();

	void Enable();

protected:

	bool AddShader(GLenum shader_type, std::string const& file_name);

	bool Finalize();

	GLint GetUniformLocation(std::string uniform_name);

	GLuint shader_prog_;

private:

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList shader_obj_list_;
};