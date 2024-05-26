#include "Engine.h"

bool Engine::init()
{
    // Initialize the library 
    if (!glfwInit())
        return false;


    // Create a windowed mode window and its OpenGL context 
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
    return true;
}

void Engine::run()
{
    //Loop until the user closes the window 
    while (!glfwWindowShouldClose(m_pWindow))
    {
        // Render here 
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers 
        glfwSwapBuffers(m_pWindow);

        // Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
}