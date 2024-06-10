#include "Shader.h"
#include <fstream>
#include <print>
#include "VertexBuffer.h"

namespace {
	struct FileHelper
	{
		FileHelper(const std::filesystem::path& fileName)
		{
			file.open(fileName);
		}

		~FileHelper()
		{
			file.close();
		}

		std::string getContentAsString()
		{
			std::stringstream stringstream;
			stringstream << file.rdbuf();
			return stringstream.str();
		}

	private:
		std::ifstream file;
	};
}


Shader::Shader(const std::filesystem::path& fileName, GLenum shaderType, VertexBuffer* vertexBuffer)
	: m_id{ glCreateShader(shaderType),[](GLuint id) {glDeleteShader(id); } }
{
	std::string shaderCode;

	try {
		FileHelper shaderFile(fileName);
		shaderCode = shaderFile.getContentAsString();
	}
	catch (const std::ifstream::failure& e)
	{
		std::println( "ERROR: Shader not read ({})",e.what());
	}

	const char* pShaderCode = shaderCode.c_str();
	glShaderSource(*m_id, 1, &(pShaderCode), nullptr);
	
	
	if (vertexBuffer)
	{
		vertexBuffer->bind();
	}

	glCompileShader(*m_id);

	GLint success = 0;
	glGetShaderiv(*m_id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int len;
		glGetShaderiv(*m_id, GL_INFO_LOG_LENGTH, &len);
		std::string errorString;
		errorString.resize(len);
		glGetShaderInfoLog(*m_id, len, nullptr, errorString.data());
		std::println("Error in Shader: {}", errorString);
	}
}
