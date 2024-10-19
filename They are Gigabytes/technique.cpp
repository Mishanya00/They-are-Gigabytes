#include "technique.hpp"
#include <iostream>
#include "mishanya_utils.hpp"


Technique::Technique()
{
	shader_prog_ = 0;
}

Technique::~Technique()
{
	for (ShaderObjList::iterator it = shader_obj_list_.begin(); it != shader_obj_list_.end(); it++)
	{
		glDeleteShader(*it);
	}

	if (shader_prog_ != 0)
	{
		glDeleteProgram(shader_prog_);
		shader_prog_ = 0;
	}
}

bool Technique::Init()
{
	shader_prog_ = glCreateProgram();

	if (shader_prog_ == 0) {
		std::cerr << "Error creating shader program\n";
		return false;
	}

	return true;
}

void Technique::Enable()
{
    glUseProgram(shader_prog_);
}

bool Technique::AddShader(GLenum shader_type, std::string const & file_name)
{
    std::string shader_code;

    if (!mishanya::ReadFile(file_name, shader_code)) {
        std::cerr << "Error reading shader file: '" << file_name << "' \n";
        return false;
    }

    GLuint ShaderObj = glCreateShader(shader_type);

    if (ShaderObj == 0) {
        std::cerr << "Error creating shader type " << shader_type << '\n';
        return false;
    }

    shader_obj_list_.push_back(ShaderObj);

    const GLchar* p[1];
    p[0] = shader_code.c_str();
    GLint Lengths[1];
    Lengths[0] = static_cast<GLint>(shader_code.size());

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        std::cerr << "Error compiling shader '" << file_name << "' " << InfoLog << '\n';
        return false;
    }

    glAttachShader(shader_prog_, ShaderObj);

    return true;
}

// Linking and validation of all previously added shaders
bool Technique::Finalize()
{
    GLint success = 0;
    GLchar error_log[1024];
    bool ret_val = true;

    glLinkProgram(shader_prog_);

    glGetProgramiv(shader_prog_, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(shader_prog_, sizeof(error_log), NULL, error_log);
        std::cerr << "Error linking shader program: '" << error_log << "'\n";
        return false;
    }

    glValidateProgram(shader_prog_);
    glGetProgramiv(shader_prog_, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_prog_, sizeof(error_log), NULL, error_log);
        std::cerr << "Invalid shader program: '" << error_log << "'\n";
        ret_val = false;
    }

    for (ShaderObjList::iterator it = shader_obj_list_.begin(); it != shader_obj_list_.end(); it++) {
        glDeleteShader(*it);
    }

    shader_obj_list_.clear();

    return (glGetError() == GL_NO_ERROR) && ret_val;
}

GLint Technique::GetUniformLocation(std::string uniform_name)
{
    GLuint Location = glGetUniformLocation(shader_prog_, uniform_name.c_str());

    // -1 means incorrect uniform location
    if (Location == -1) {
        std::cerr << "Warning! Unable to get the location of uniform '" << uniform_name << "'\n";
    }

    return Location;
}
