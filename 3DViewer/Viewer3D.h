#pragma once
#include "Engine.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>
#include "Camera.h"

class Viewer3D : public Engine
{
	void onCreate() override;
    void onUpdate(double deltaTime) override;

private:
    void initCube();
    void handleInput(double deltaTime);
    void draw();

    struct Renderable
    {
        ShaderProgram m_shaderProgram;
        VertexBuffer m_vertexBuffer;

        glm::mat4 m_modelTransform{ glm::scale(glm::mat4{ 1.0f }, glm::vec3{0.2f,0.2f,0.2f}) };
        GLuint m_modelTransformID{};
        GLuint m_modelTransformNormalID{};
    };
    std::optional<Renderable> m_cube{ std::nullopt };


    Camera m_camera;

    bool m_firstMouse{ true };
    glm::vec2 m_lastMousePos;
};

