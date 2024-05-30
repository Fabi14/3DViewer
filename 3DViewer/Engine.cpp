#include "Engine.h"

#include <glm/glm.hpp>
#include "DebugOutput.h"
#include "Vertex.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"

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

    // set clear color
    glClearColor(0.f, 0.f, 0.5f, 1.0f);

    //init and bind Shader and VertexArrayObject for first triangle
    initTriangle();

    return true;
}

void Engine::initTriangle()
{
    std::vector<Vertex> triangleVertices{
        Vertex{ .pos{ -0.5f,-0.5f,0.f } }
        ,Vertex{ .pos{ 0.5f,-0.5f,0.f } }
        ,Vertex{ .pos{ 0.f,0.5f,0.f } }
    };
    VertexBuffer vertexArrayObject{ triangleVertices };
    
    const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER ,&vertexArrayObject };
    const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    m_triangle = Triangle{
        ShaderProgram{ vertexShader, fragmentShader }
        , std::move(vertexArrayObject)
    };
}

void Engine::run()
{
    //Loop until the user closes the window 
    while (!glfwWindowShouldClose(m_pWindow))
    {
        // clear buffer and draw triangle
        draw();

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

void Engine::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_triangle)
    {
        m_triangle->m_vertexBuffer.bind();
        m_triangle->m_shaderProgram.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
