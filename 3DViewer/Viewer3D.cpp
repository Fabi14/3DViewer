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

    initQuad();
}

void Viewer3D::onUpdate()
{
    draw();
}

void Viewer3D::initQuad()
{
    Mesh quad{ getQuadMesh() };

    VertexBuffer vertexArrayObject{ quad.m_vertices, quad.m_indices };

    const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER ,&vertexArrayObject };
    const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    m_quad = Renderable{
        .m_shaderProgram = ShaderProgram{ vertexShader, fragmentShader },
        .m_vertexBuffer = std::move(vertexArrayObject)
    };

    m_quad->m_modelTransformID = glGetUniformLocation(m_quad->m_shaderProgram.get(), "modelTransform");
    m_quad->m_modelNormalTransformID = glGetUniformLocation(m_quad->m_shaderProgram.get(), "modelNormalTransform");

    // light
    m_lightDirID = glGetUniformLocation(m_quad->m_shaderProgram.get(), "lightDir");
    const glm::vec3 lightDir{ glm::vec3(0.0f, 0.0f, 1.0f) };
    m_quad->m_shaderProgram.use();
    glUniform3fv(m_lightDirID, 1, &lightDir.x);
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_quad) // TODO: move code into Renderable
    {
        m_quad->m_vertexBuffer.bind();
        m_quad->m_shaderProgram.use();

        float angle{2.f};  // TODO: use deltaTime  (glfwGetTime())
        m_quad->m_modelTransform = glm::rotate(m_quad->m_modelTransform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(m_quad->m_modelTransformID, 1, GL_FALSE, &m_quad->m_modelTransform[0][0]);

        auto normalTransform = glm::inverse(glm::mat3(m_quad->m_modelTransform));
        glUniformMatrix3fv(m_quad->m_modelNormalTransformID, 1, GL_FALSE, &normalTransform[0][0]);

        glDrawElements(GL_TRIANGLES,m_quad->m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
    }
}
