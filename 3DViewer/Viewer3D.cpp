#include "Viewer3D.h"
#include "Shader.h"
#include <sstream>
#include <print>
#include "Mesh.h"
#include "MeshImporter.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

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
    handleInput(deltaTime);

    draw();
}

void Viewer3D::initCube()
{
    //Mesh mesh{ getCubeMesh() };
    //Mesh mesh{ MeshImporter::importFile("teapot.stl").value()};
    {
        auto model = Model{ MeshImporter::importFile("..\\Models\\Dinosaur\\Models\\Dinosaur_low.fbx").value() };

        const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER };
        const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

        model.m_shaderProgram = ShaderProgram{ vertexShader, fragmentShader };

        model.m_modelTransformID = glGetUniformLocation(model.m_shaderProgram.get(), "modelTransform");
        model.m_modelTransformNormalID = glGetUniformLocation(model.m_shaderProgram.get(), "modelTransformNormal");

        m_models.push_back(std::move(model));
    }
    {
        auto model = Model{ MeshImporter::importFile("teapot.stl").value() };

        const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER };
        const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

        model.m_shaderProgram = ShaderProgram{ vertexShader, fragmentShader };

        model.m_modelTransformID = glGetUniformLocation(model.m_shaderProgram.get(), "modelTransform");
        model.m_modelTransformNormalID = glGetUniformLocation(model.m_shaderProgram.get(), "modelTransformNormal");

        m_models.push_back(std::move(model));
    }
}

void Viewer3D::handleInput(double deltaTime)
{
    glm::vec3 tmpdir{ m_camera.getDirection()}; //fps steuerung
    constexpr float speed{ 50.f };
    const auto fTime{ static_cast<float>(deltaTime) };

    if (getKey(GLFW_KEY_W))
        m_camera.position += (tmpdir * fTime * speed);
    if (getKey(GLFW_KEY_S))
        m_camera.position += (-tmpdir * fTime * speed);
    if (getKey(GLFW_KEY_A))
        m_camera.position += (glm::normalize(glm::cross(m_camera.up, tmpdir)) * fTime * speed);
    if (getKey(GLFW_KEY_D))
        m_camera.position += (-glm::normalize(glm::cross(m_camera.up, tmpdir)) * fTime * speed);

    
    glm::vec2 newMousePos = getMousePos();

    if (m_firstMouse)
    {
        m_lastMousePos = newMousePos;
        m_firstMouse = false;
    }

    float xoffset{ newMousePos.x - m_lastMousePos.x };
    float yoffset{ m_lastMousePos.y - newMousePos.y };

    m_lastMousePos = newMousePos;

    float angularVelocity{ 0.1f };
    xoffset *= angularVelocity;
    yoffset *= angularVelocity;

    m_camera.yaw += xoffset;
    m_camera.pitch += yoffset;

    m_camera.pitch = glm::clamp(m_camera.pitch, -89.0f, 89.0f);
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (m_models.empty())
    {
        return;
    }

    for (const auto& model : m_models)
    {
        for (const auto& renderable : model.m_vecRenderables)
        {
            renderable.m_vertexBuffer.bind();
            model.m_shaderProgram.use();

            glUniformMatrix4fv(model.m_modelTransformID, 1, GL_FALSE, &renderable.m_modelTransform[0][0]);

            auto normalMatrix{ glm::inverse(glm::mat3(renderable.m_modelTransform)) };
            glUniformMatrix3fv(model.m_modelTransformNormalID, 1, GL_TRUE, &normalMatrix[0][0]);

            model.m_shaderProgram.addCameraTransform(m_camera.getViewTransform(), m_camera.m_projectionTransform);

            glDrawElements(GL_TRIANGLES, renderable.m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
        }
    }
}
