#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>
#include "ShaderProgram.h"
#include "VertexBuffer.h"


class Engine
{
public:
    bool init();
    void run();

private:
    void draw();
    void initTriangle();

    GLFWwindow* m_pWindow;

    struct Triangle
    {
        ShaderProgram m_shaderProgram;
        VertexBuffer m_vertexBuffer;
    };
    std::optional<Triangle> m_triangle{ std::nullopt };
};

