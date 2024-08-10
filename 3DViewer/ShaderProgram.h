#pragma once
#include <memory>
#include <glad/glad.h>
#include "UniqueResource.h"

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmenShader);
	ShaderProgram() :m_id{} {}
	void use() const;

	GLuint get() { return *m_id; }
private:
	UniqueResource m_id{ glCreateProgram(),[](GLuint id){ glDeleteProgram(id); }};
};

