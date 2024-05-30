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
	static void deleteVao(GLuint id);

	UniqueResource m_vao{ createVao(), &deleteVao };
};

