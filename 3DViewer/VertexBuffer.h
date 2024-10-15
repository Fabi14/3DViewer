#pragma once
#include <vector>
#include "Vertex.h"
#include "UniqueResource.h"

using Index = unsigned int;

class VertexBuffer
{
public:

	VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices, const std::vector<InstanceData>& vecInstanceData = { {glm::mat4(1.f)} });

	void bind() const;
	GLsizei getIndexCount() const
	{
		return m_indexCount;
	}

	GLsizei getInstanceCount() const 
	{
		return m_instanceCount;
	}

private:
	VertexBuffer(const std::vector<Vertex>& vecVertices);
	//VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices);

	static GLuint createVao();
	static GLuint createBuffer();
	static void deleteVao(GLuint id);
	static void deleteBuffer(GLuint id);

	UniqueResource m_vao{ createVao(), &deleteVao };
	UniqueResource m_vbo{ createBuffer(), &deleteBuffer };
	UniqueResource m_instanceVbo{ createBuffer(), &deleteBuffer };
	UniqueResource m_ebo{ createBuffer(), &deleteBuffer };

	GLsizei m_indexCount{};
	GLsizei m_instanceCount{};
};

