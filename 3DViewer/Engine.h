#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>
#include "ShaderProgram.h"
#include "VertexBuffer.h"


class Engine
{
public:
    virtual ~Engine() = default;

    bool init();
    void run();

private:
    virtual void onCreate() = 0;
    virtual void onUpdate(double deltaTime) = 0;

    GLFWwindow* m_pWindow;
    double m_time{};
};

