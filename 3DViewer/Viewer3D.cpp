#include "Viewer3D.h"
#include "Shader.h"

void Viewer3D::onCreate()
{
    // set clear color
    glClearColor(0.f, 0.f, 0.5f, 1.0f);

    initTriangle();
}

void Viewer3D::onUpdate()
{
    draw();
}

void Viewer3D::initTriangle()
{
    std::vector<Vertex> triangleVertices{
        Vertex{.pos{ -0.5f,-0.5f,0.f } }
        ,Vertex{.pos{ 0.5f,-0.5f,0.f } }
        ,Vertex{.pos{ 0.f,0.5f,0.f } }
    };
    VertexBuffer vertexArrayObject{ triangleVertices };

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
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
