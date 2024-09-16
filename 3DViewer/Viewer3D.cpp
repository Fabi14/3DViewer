#include "Viewer3D.h"
#include "Shader.h"
#include <sstream>
#include <print>
#include "Mesh.h"
#include "MeshImporter.h"

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


    Mesh getCubeMesh()
    {
        return Mesh{
            {
                //front
                {{-0.5f, -0.5f, 0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
                {{-0.5f,  0.5f, 0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f,  0.5f, 0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f, -0.5f, 0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, 1.0f}},

                //back	  
                {{ 0.5f, -0.5f,-0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
                {{ 0.5f,  0.5f,-0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
                {{-0.5f,  0.5f,-0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f}},
                {{-0.5f, -0.5f,-0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, -1.0f}},

                //left
                {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
                {{-0.5f,  0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
                {{-0.5f,  0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}},
                {{-0.5f, -0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {-1.0f, 0.0f, 0.0f}},

                //right
                {{0.5f, -0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {1.0f, 0.0f, 0.0f}},

                //top
                {{-0.5f, 0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
                {{-0.5f, 0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.5f, 0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.5f, 0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 1.0f, 0.0f}},

                //bottom
                {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
                {{-0.5f, -0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
                {{ 0.5f, -0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}},
                {{ 0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, -1.0f, 0.0f}},
            },
            {

                0,3,2,0,2,1,
                0 + 4,3 + 4,2 + 4,0 + 4,2 + 4,1 + 4,
                0 + 8,3 + 8,2 + 8,0 + 8,2 + 8,1 + 8,
                0 + 12,3 + 12,2 + 12,0 + 12,2 + 12,1 + 12,
                0 + 16,3 + 16,2 + 16,0 + 16,2 + 16,1 + 16,
                0 + 20,3 + 20,2 + 20,0 + 20,2 + 20,1 + 20,
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

    initTeapot();
}

void Viewer3D::initTeapot()
{
    //MeshImporter::DoTheImportThing("C:\\Users\\fabia\\source\\repos\\3DViewer\\3DViewer\\Teapot.stl");
}

void Viewer3D::onUpdate()
{
    float angle{ 1.f };  // TODO: use deltaTime  (glfwGetTime())
    m_quad->m_modelTransform = glm::rotate(m_quad->m_modelTransform, glm::radians(angle), glm::vec3(0.0f, 1.0f, .2f));

    draw();
}

void Viewer3D::initQuad()
{
    Mesh mesh{ MeshImporter::DoTheImportThing("C:\\Users\\fabia\\source\\repos\\3DViewer\\3DViewer\\Teapot.stl").value()};
   //Mesh mesh{ getCubeMesh() };


    VertexBuffer vertexArrayObject{ mesh.m_vertices, mesh.m_indices };

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
    const glm::vec3 lightDir{ glm::vec3(0.3f,.2f, -1.0f) };
    m_quad->m_shaderProgram.use();
    glUniform3fv(m_lightDirID, 1, &lightDir.x);

    float angle{ 0.f }; 
    m_quad->m_modelTransform = glm::rotate(m_quad->m_modelTransform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    m_quad->m_modelTransform = glm::rotate(m_quad->m_modelTransform, glm::radians(-15.f), glm::vec3(1.0f, 0.0f, .0f));
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_quad) // TODO: move code into Renderable
    {
        m_quad->m_vertexBuffer.bind();
        m_quad->m_shaderProgram.use();

        glUniformMatrix4fv(m_quad->m_modelTransformID, 1, GL_FALSE, &m_quad->m_modelTransform[0][0]);

        auto normalTransform = glm::transpose(glm::inverse(glm::mat3(m_quad->m_modelTransform)));
        glUniformMatrix3fv(m_quad->m_modelNormalTransformID, 1, GL_FALSE, &normalTransform[0][0]);

        glDrawElements(GL_TRIANGLES,m_quad->m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
    }
}
