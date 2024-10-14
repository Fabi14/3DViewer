#pragma once
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

struct Renderable
{
    VertexBuffer m_vertexBuffer;

    glm::mat4 m_modelTransform{ glm::scale(glm::mat4{ 1.0f }, glm::vec3{0.2f,0.2f,0.2f}) };
};

struct Model
{
    ShaderProgram m_shaderProgram;
    GLuint m_modelTransformID{};
    GLuint m_modelTransformNormalID{};

    std::vector<Renderable> m_vecRenderables{};
};

