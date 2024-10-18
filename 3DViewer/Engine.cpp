
#include "Engine.h"

//#include <glm/glm.hpp>
#include "DebugOutput.h"
#include "Vertex.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"

namespace {
    void onSize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

bool Engine::init()
{
    // Initialize the library 
    if (!glfwInit())
        return false;


    // Create a windowed mode window and its OpenGL context 

#ifdef _DEBUG
    //  create OpenGL in debug mode (required for DebugOutput)
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
#endif

    m_pWindow = glfwCreateWindow(640*2, 480*2, "Graphics Programming", nullptr, nullptr);
    if (!m_pWindow)
    {
        glfwTerminate();
        return false;
    }
    //glfwSetWindowPos(m_pWindow, 4000, 1100);
    glfwSetWindowSizeCallback(m_pWindow, onSize);

    // Make the window's context current 
    glfwMakeContextCurrent(m_pWindow);

    // Load all OpenGL functions using the glfw loader function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#ifdef _DEBUG
    DebugOutput::enable();
#endif
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    onCreate();

    return true;
}


void Engine::run()
{
    //Loop until the user closes the window 
    while (!glfwWindowShouldClose(m_pWindow))
    {
        // clear buffer and draw triangle
        auto now = glfwGetTime();
        auto deltaTime = now - m_time;
        m_time = now;
        onUpdate(deltaTime);

        // Swap front and back buffers 
        glfwSwapBuffers(m_pWindow);

        // Poll for and process events 
        glfwPollEvents();

        if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
        }
    }

    glfwTerminate();
}

bool Engine::getKey(int key)
{
    if (m_pWindow)
    {
        return glfwGetKey(m_pWindow, key) == GLFW_PRESS;
    }
    return false;
}

glm::vec2 Engine::getMousePos()
{
    double xpos{};
    double ypos{};

    if (m_pWindow)
    {
        glfwGetCursorPos(m_pWindow, &xpos, &ypos);
    }
    return { xpos, ypos };
}

bool Engine::getMouseButton(int button)
{
    if (m_pWindow)
    {
       return glfwGetMouseButton(m_pWindow, button) == GLFW_PRESS;
    }
    return false;
}


