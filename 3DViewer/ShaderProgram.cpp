#include "ShaderProgram.h"
#include "Shader.h"


ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);
	glValidateProgram(*m_id);

	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());

	m_viewTransformId = glGetUniformLocation(*m_id, "viewTransform");
	m_projectionTransformId = glGetUniformLocation(*m_id, "projectionTransform");
}

void ShaderProgram::use() const
{
	glUseProgram(*m_id);
}

void ShaderProgram::addCameraTransform(
	const glm::mat4& viewTransform, 
	const glm::mat4& projectionTransform)
{
	glUniformMatrix4fv(m_viewTransformId, 1, GL_FALSE, &viewTransform[0][0]);
	glUniformMatrix4fv(m_projectionTransformId, 1, GL_FALSE, &projectionTransform[0][0]);
}
