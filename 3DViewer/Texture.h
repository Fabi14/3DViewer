#pragma once
#include <string>
#include "UniqueResource.h"
#include "ShaderProgram.h"

class Texture
{
public:
	Texture(const std::string& filename, const ShaderProgram& shader, const std::string& uniformname, unsigned int id);

	void bind() const;

private:

	UniqueResource m_id{ []() {
		GLuint id;
		glGenTextures(1, &id);
		return id;
		}(),
		[](GLuint id) {glDeleteTextures(1, &id); } };

	unsigned int m_unit;
};

