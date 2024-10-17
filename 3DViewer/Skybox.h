#pragma once
#include "Model.h"
#include "ShaderProgram.h"

class Camera;

class Skybox
{
public:
	Skybox();
	void draw(const Camera&) const;

private:
	Model m_cube;
	ShaderProgram m_shaderProgram;

	UniqueResource m_texId{ []() {
	GLuint id;
	glGenTextures(1, &id);
	return id;
	}(),
	[](GLuint id) {glDeleteTextures(1, &id); } };
};

