#include "Texture.h"
#include "ShaderProgram.h"
#include "Image.h"



Texture::Texture(const std::string& filename, const ShaderProgram& shader, const std::string& uniformname, unsigned int id):m_unit{id}
{
	Image image(filename);

	if (image.m_buffer)
	{
		glBindTexture(GL_TEXTURE_2D, *m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.m_width, image.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.m_buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		auto texUniform = glGetUniformLocation(shader.get(), uniformname.c_str());
		glUniform1i(texUniform, m_unit);
	}
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, *m_id);
}
