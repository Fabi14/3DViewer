#include "Viewer3D.h"
#include "Shader.h"
#include <sstream>
#include <print>
#include "Mesh.h"

namespace {
    std::string getGlInfoString()
    {
        std::stringstream info;
        info << "VENDOR: " << glGetString(GL_VENDOR) << '\n';
        info << "VERSION: " << glGetString(GL_VERSION) << '\n';
        info << "RENDERER: " << glGetString(GL_RENDERER) << '\n';
        info << "SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
        return info.str();
    }

    Mesh getQuadMesh()
    {
        return Mesh{ 
            {   // vertices
                //			pos						color					normal
                { {-0.5f, -0.5f, 0.0f}, {0.0f,0.5f,0.1f,1.0f},   {0.0f, 0.0f, 1.0f}},
                { {-0.5f,  0.5f, 0.0f},	{1.0f,0.5f,0.1f,1.0f},   {0.0f, 0.0f, 1.0f} },
                { { 0.5f,  0.5f, 0.0f},	{0.5f,0.5f,0.1f,1.0f},   {0.0f, 0.0f, 1.0f} },
                { { 0.5f, -0.5f, 0.0f},	{0.0f,0.5f,1.0f,1.0f},   {0.0f, 0.0f, 1.0f} },
            },
            {   // indices
                0,3,2,0,2,1
            } 
        };
    }
}


void Viewer3D::onCreate()
{
    // set clear color
    glClearColor(0.f, 0.f, 0.5f, 1.0f);
    std::println("{}", getGlInfoString());

    initTriangles();
}

void Viewer3D::onUpdate()
{
    draw();
}

void Viewer3D::initTriangles()
{
    Mesh quad{ getQuadMesh() };

    VertexBuffer vertexArrayObject{ quad.m_vertices, quad.m_indices };

    const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER ,&vertexArrayObject };
    const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    m_triangle = Triangle{
        ShaderProgram{ vertexShader, fragmentShader }
        , std::move(vertexArrayObject)
    };
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_triangle)
    {
        m_triangle->m_vertexBuffer.bind();
        m_triangle->m_shaderProgram.use();
        glDrawElements(GL_TRIANGLES, m_triangle->m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
    }
}
