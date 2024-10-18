#include "ShaderProgram.h"
#include "Shader.h"
#include <print>


ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);
	glValidateProgram(*m_id);
	int len;
	glGetProgramiv(*m_id, GL_INFO_LOG_LENGTH, &len);
	if (len != 0)
	{
		std::string errorString;
		errorString.resize(len);
		glGetProgramInfoLog(*m_id, len, nullptr, errorString.data());
		std::println("Shader Program Log: {}", errorString);
	}
	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());
	glUseProgram(*m_id);
	m_modelTransformID = glGetUniformLocation(*m_id, "modelTransform");
	m_modelTransformNormalID = glGetUniformLocation(*m_id, "modelTransformNormal");

	m_viewTransformId = glGetUniformLocation(*m_id, "viewTransform");
	m_projectionTransformId = glGetUniformLocation(*m_id, "projectionTransform");

	m_viewPosId = glGetUniformLocation(*m_id, "viewPos");
}

void ShaderProgram::use() const
{
	glUseProgram(*m_id);
}

void ShaderProgram::addCameraTransform(
	const glm::mat4& viewTransform, 
	const glm::mat4& projectionTransform) const
{
	glUniformMatrix4fv(m_viewTransformId, 1, GL_FALSE, &viewTransform[0][0]);
	glUniformMatrix4fv(m_projectionTransformId, 1, GL_FALSE, &projectionTransform[0][0]);
}

void ShaderProgram::addModelTransform(
	const glm::mat4& modelTransform,
	const glm::mat4& normalTransfor) const
{
	glUniformMatrix4fv(m_modelTransformID, 1, GL_FALSE, &modelTransform[0][0]);
	glUniformMatrix3fv(m_modelTransformNormalID, 1, GL_TRUE, &normalTransfor[0][0]);
}

void ShaderProgram::setViewPos(
	const glm::vec3& viewPos) const
{
	glUniform3fv(m_viewPosId, 1, &(viewPos.x));
}
