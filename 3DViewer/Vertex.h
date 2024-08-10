#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 normal;
};