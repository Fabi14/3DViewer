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

    initCube();
}

void Viewer3D::onUpdate(double deltaTime)
{
    float angle{ 1.f };  // TODO: use deltaTime  (glfwGetTime())
    m_cube->m_modelTransform = glm::rotate(m_cube->m_modelTransform, glm::radians(angle), glm::vec3(0.0f, 1.0f, .0f));

    handleInput(deltaTime);

    draw();
}

void Viewer3D::initCube()
{
    //Mesh mesh{ getCubeMesh() };
    Mesh mesh{ MeshImporter::importFile("teapot.stl").value()};

    VertexBuffer vertexArrayObject{ mesh.m_vertices, mesh.m_indices };

    const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER ,&vertexArrayObject };
    const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    m_cube = Renderable{
        .m_shaderProgram = ShaderProgram{ vertexShader, fragmentShader },
        .m_vertexBuffer = std::move(vertexArrayObject)
    };

    m_cube->m_modelTransformID = glGetUniformLocation(m_cube->m_shaderProgram.get(), "modelTransform");
    m_cube->m_modelTransformNormalID = glGetUniformLocation(m_cube->m_shaderProgram.get(), "modelTransformNormal");
    
    float angle{ 0.f };
    //m_cube->m_modelTransform = glm::rotate(m_cube->m_modelTransform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    m_cube->m_modelTransform = glm::rotate(m_cube->m_modelTransform, glm::radians(-30.f), glm::vec3(1.0f, 0.0f, .0f));
}

void Viewer3D::handleInput(double deltaTime)
{
    //TODO
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_cube) // TODO: move code into Renderable
    {
        m_cube->m_vertexBuffer.bind();
        m_cube->m_shaderProgram.use();

        glUniformMatrix4fv(m_cube->m_modelTransformID, 1, GL_FALSE, &m_cube->m_modelTransform[0][0]);

        auto normalMatrix{glm::inverse(glm::mat3(m_cube->m_modelTransform)) };
        glUniformMatrix3fv(m_cube->m_modelTransformNormalID, 1, GL_TRUE, &normalMatrix[0][0]);

        m_cube->m_shaderProgram.addCameraTransform(m_camera.getViewTransform(), m_camera.m_projectionTransform);

        glDrawElements(GL_TRIANGLES,m_cube->m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
    }
}
