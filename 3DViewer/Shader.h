#pragma once
#include <filesystem>
#include <glad/glad.h>
#include "UniqueResource.h"
		
class VertexBuffer;

class Shader
{
public:
	Shader(const std::filesystem::path& fileName, GLenum shaderType, VertexBuffer* vertexBuffer = nullptr);

	GLuint get() const { return *m_id; }

private:
	UniqueResource m_id{};
};

