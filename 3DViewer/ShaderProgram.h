#pragma once
#include <memory>
#include <glad/glad.h>
#include "UniqueResource.h"
#include <glm/ext/matrix_float4x4.hpp>

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmenShader);
	ShaderProgram() :m_id{} {}
	void use() const;

	GLuint get() const { return *m_id; }
	void addCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform) const;
private:
	UniqueResource m_id{ glCreateProgram(),[](GLuint id){ glDeleteProgram(id); }};

	GLuint m_viewTransformId;
	GLuint m_projectionTransformId;
};

