#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

class Camera
{
public:
    Camera() : m_projectionTransform{glm::perspective(glm::radians(30.f), 640.f / 480.f, 0.1f, 100.f)}
    {
    }


    glm::mat4 m_viewTransform{ 1.f };
    glm::mat4 m_projectionTransform{ 1.f };
};

