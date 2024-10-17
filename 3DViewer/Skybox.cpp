#include "Skybox.h"
#include "MeshImporter.h"
#include "Image.h"
#include "Shader.h"
#include <array>
#include <string>
#include <ranges>
#include "Camera.h"

namespace
{
	const std::array<std::string, 6> c_skyboxImageNames
	{
		"..\\Models\\Skybox\\right.jpg",
		"..\\Models\\Skybox\\left.jpg",
		"..\\Models\\Skybox\\top.jpg",
		"..\\Models\\Skybox\\bottom.jpg",
		"..\\Models\\Skybox\\front.jpg",
		"..\\Models\\Skybox\\back.jpg",
	};
}



Skybox::Skybox()
{
	// Cube Model
	m_cube = MeshImporter::getCube();

	// Bilder cube map laden

	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (const auto& [i , filename] : std::views::enumerate( c_skyboxImageNames))
	{
		Image image{ filename,false };

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, image.m_width, image.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.m_buffer);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//Shader anlegen
	m_shaderProgram = ShaderProgram(Shader("SkyboxVertexShader.glsl", GL_VERTEX_SHADER), Shader("SkyboxFragmentShader.glsl", GL_FRAGMENT_SHADER));
}

void Skybox::draw(const Camera& camera) const
{
	//Shader aktivieren
	m_shaderProgram.use();

	auto viewDirTrans = glm::mat3(camera.getViewTransform());
	m_shaderProgram.addCameraTransform(glm::mat4(viewDirTrans),camera.m_projectionTransform );

	// cube map texture 
	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);

	// Cube binden
	m_cube.m_vecRenderables[0].m_vertexBuffer.bind();

	GLint oldFaceMode{};
	glGetIntegerv(GL_CULL_FACE_MODE, &oldFaceMode);
	GLint oldDepthMode{};
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthMode);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	// Zeichnen Innenflächen 
	glDrawElements(GL_TRIANGLES, m_cube.m_vecRenderables[0].m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);

	glCullFace(oldFaceMode);
	glDepthFunc(oldDepthMode);

}


