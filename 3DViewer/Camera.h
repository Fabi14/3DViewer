#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

class Camera
{
public:
    Camera() : m_projectionTransform{ glm::perspective(glm::radians(30.f), 640.f / 480.f, 0.1f, 500.f) }
    {
    }

    glm::mat4 getViewTransform()
    {


        return glm::lookAt(position, position + getDirection(), up);
    }

    glm::vec3 getDirection()
    {
        glm::vec3 dir{
    cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
    sin(glm::radians(pitch)),
    sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        };

        auto rotateX = glm::rotate(glm::radians(pitch), glm::vec3{1.f,0.f,0.f });
        auto rotateY = glm::rotate(glm::radians(yaw), glm::vec3{ 0.f,1.f,0.f });

        auto dir2{ rotateX * rotateY * glm::vec4{0.f,0.f,1.f,0.f} };

        return glm::normalize(dir);
    }


    glm::mat4 m_projectionTransform{ 1.f };

    glm::vec3 position{ 0.0f, 0.0f, -5.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };

    float yaw{ 90.0f };
    float pitch{};
};

