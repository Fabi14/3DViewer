#pragma once
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>
#include "Texture.h"
#include <optional>

struct Renderable
{
    VertexBuffer m_vertexBuffer;

    glm::mat4 m_modelTransform{ glm::scale(glm::mat4{ 1.0f }, glm::vec3{0.2f,0.2f,0.2f}) };
};

struct Model
{
    std::optional<Texture> m_texture;

    std::vector<Renderable> m_vecRenderables{};
};

