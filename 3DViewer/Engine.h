#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
    bool init();
    void run();

private:
    GLFWwindow* m_pWindow;
};

