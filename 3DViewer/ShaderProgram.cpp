#include "ShaderProgram.h"
#include "Shader.h"


ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);

	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());
}

void ShaderProgram::use() const
{
	glUseProgram(*m_id);
}
