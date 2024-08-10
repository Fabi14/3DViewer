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

    std::vector<Vertex> getTriangleVertices()
    {
        return std::vector<Vertex>{
             Vertex{.pos{ -0.5f,-0.5f,0.f },.col{1.f,0.f,1.f,1.f} }
            ,Vertex{.pos{ 0.5f,-0.5f,0.f },.col{1.f,1.f,0.f,1.f}  }
            ,Vertex{.pos{ 0.5f,0.5f,0.f },.col{1.f,0.f,0.f,1.f} }
            ,Vertex{.pos{ 0.5f,0.5f,0.f },.col{1.f,0.f,0.f,1.f} }
            ,Vertex{.pos{ -0.5f,0.5f,0.f },.col{1.f,1.f,0.f,1.f}  }
            ,Vertex{.pos{ -0.5f,-0.5f,0.f },.col{1.f,0.f,1.f,1.f} }
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
    Mesh triangle{ getTriangleVertices() };

    VertexBuffer vertexArrayObject{ triangle.m_vertices };

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
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
