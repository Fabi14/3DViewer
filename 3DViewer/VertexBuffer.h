#pragma once
#include <vector>
#include "Vertex.h"
#include "UniqueResource.h"

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex>& vecVertices);

	void bind();

private:
	static GLuint createVao();
	static GLuint createVbo();
	static void deleteVao(GLuint id);
	static void deleteVbo(GLuint id);

	UniqueResource m_vao{ createVao(), &deleteVao };
	UniqueResource m_vbo{ createVbo(), &deleteVbo };
};

