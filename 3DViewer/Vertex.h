#pragma once
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glad/glad.h>
#include <type_traits>


struct Attribut
{
	GLint m_size{};
	GLenum m_type{};
	GLboolean m_normalized{};
	GLsizei m_stride{};
	const GLvoid* m_pointer{};
};

template <typename Type>
GLenum getTypeEnum()
{
	if constexpr(std::is_same_v<Type, float>)
	{
		return GL_FLOAT;
	}
	return 0;
}

template <typename VertexType, typename AttributType>
Attribut createAttribut(size_t offset, GLboolean normalized = GL_FALSE) {

	return Attribut{
		.m_size{ AttributType::length() },
		.m_type{ getTypeEnum<typename AttributType::value_type>()},
		.m_normalized{ normalized },
		.m_stride{ static_cast<GLsizei>(sizeof(VertexType)) },
		.m_pointer{ reinterpret_cast<void*>(offset) }
	};
}

struct VertexLayout
{
	std::vector<Attribut> m_vecAttributs;
};


struct Vertex
{
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 normal;
	glm::vec2 uvs;

	static VertexLayout getLayout()
	{
		return { .m_vecAttributs =
			{
			createAttribut<Vertex, glm::vec3>(offsetof(Vertex, pos)),
			createAttribut<Vertex, glm::vec4>(offsetof(Vertex, col)),
			createAttribut<Vertex, glm::vec3>(offsetof(Vertex, normal)),
			createAttribut<Vertex, glm::vec2>(offsetof(Vertex, uvs)),
			}
		};

	}
};

struct InstanceData
{
	glm::vec3 pos;

	static VertexLayout getLayout()
	{
		return { .m_vecAttributs =
			{
			createAttribut<InstanceData, glm::vec3>(offsetof(Vertex, pos))
			}
		};

	}
};