#pragma once
#include <glm/ext/matrix_float4x4.hpp>

class Camera
{
public:
    glm::mat4 m_viewTransform{ };
    glm::mat4 m_projectionTransform{ };
};

