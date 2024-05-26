#include "Engine.h"
#include "DebugOutput.h"

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

    m_pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_pWindow)
    {
        glfwTerminate();
        return false;
    }

    // Make the window's context current 
    glfwMakeContextCurrent(m_pWindow);

    // Load all OpenGL functions using the glfw loader function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }

#ifdef _DEBUG
    DebugOutput::enable();
#endif
    return true;
}

void Engine::run()
{
    //Loop until the user closes the window 
    while (!glfwWindowShouldClose(m_pWindow))
    {
        // set clear color
        glClearColor(0.f, 0.f, 0.5f, 1.0f);

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

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
