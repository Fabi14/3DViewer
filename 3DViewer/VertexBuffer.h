#pragma once
#include <vector>
#include "Vertex.h"
#include "UniqueResource.h"

using Index = unsigned int;

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex>& vecVertices);
	VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices);

	void bind();
	GLsizei getIndexCount()
	{
		return m_indexCount;
	}

private:
	static GLuint createVao();
	static GLuint createBuffer();
	static void deleteVao(GLuint id);
	static void deleteBuffer(GLuint id);

	UniqueResource m_vao{ createVao(), &deleteVao };
	UniqueResource m_vbo{ createBuffer(), &deleteBuffer };
	UniqueResource m_ebo{ createBuffer(), &deleteBuffer };

	GLsizei m_indexCount{};
};

