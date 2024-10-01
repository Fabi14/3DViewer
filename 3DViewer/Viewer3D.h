#pragma once
#include "Engine.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate() override;

private:
    void initCube();
    void draw();

    struct Renderable
    {
        ShaderProgram m_shaderProgram;
        VertexBuffer m_vertexBuffer;

        glm::mat4 m_modelTransform{ glm::scale(glm::mat4{ 1.0f }, glm::vec3{0.5f,0.5f,0.5f}) };
        GLuint m_modelTransformID{};
        GLuint m_modelTransformNormalID{};
    };
    std::optional<Renderable> m_cube{ std::nullopt };

    GLuint m_lightDirID{};
};

