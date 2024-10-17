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
}


void Viewer3D::onCreate()
{
    // set clear color
    glClearColor(0.f, 0.f, 0.5f, 1.0f);
    std::println("{}", getGlInfoString());
    glEnable(GL_STENCIL_TEST);


    const Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER };
    const Shader fragmentShaderSingleColor{ "FragmentShaderSingleColor.glsl", GL_FRAGMENT_SHADER };
    m_shaderProgramSingleColor = ShaderProgram{ vertexShader,fragmentShaderSingleColor };

    const Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    m_shaderProgramTexture = ShaderProgram{ vertexShader, fragmentShader };
   
    initModels();
}

void Viewer3D::onUpdate(double deltaTime)
{
    handleInput(deltaTime);

    draw();
}

void Viewer3D::initModels()
{
    //Mesh mesh{ getCubeMesh() };
    //Mesh mesh{ MeshImporter::importFile("teapot.stl").value()};
    {
        auto model = Model{ MeshImporter::importFile("..\\Models\\Dinosaur\\Models\\Dinosaur_low.fbx").value() };



        model.m_texture = Texture("..\\Models\\Dinosaur\\Textures\\Texture Maps after Baking\\T_Dinosaur_BC.png", *m_shaderProgramTexture,"baseColorTexture",0);

        m_models.push_back(std::move(model));
    }
    {
        auto model = Model{ MeshImporter::importFile("teapot.stl").value() };

        m_models.push_back(std::move(model));
    }
    {
        auto model = Model{ MeshImporter::getCube()};


        model.m_texture = Texture("..\\Models\\SAELogo.png", *m_shaderProgramTexture, "baseColorTexture", 0);

        model.m_vecRenderables.front().m_modelTransform *= glm::scale(glm::vec3{ 30.f,30.f,30.f }) * glm::translate(glm::vec3{ 2.f,0.f,0.f });

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

void Viewer3D::drawModel(ShaderProgram& shader, const Model& model, const glm::mat4& mat)
{
    shader.use();
    for (const auto& renderable : model.m_vecRenderables)
    {
        renderable.m_vertexBuffer.bind();

        if (model.m_texture)
        {
            model.m_texture->bind();

        }


        auto updatedModelTransform = renderable.m_modelTransform * mat;
        auto normalMatrix{ glm::inverse(glm::mat3(updatedModelTransform)) };
        shader.addModelTransform(updatedModelTransform, normalMatrix);

        shader.addCameraTransform(m_camera.getViewTransform(), m_camera.m_projectionTransform);

        if (renderable.m_vertexBuffer.getInstanceCount() == 0)
        {
            glDrawElements(GL_TRIANGLES, renderable.m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawElementsInstanced(GL_TRIANGLES, renderable.m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0, renderable.m_vertexBuffer.getInstanceCount());
        }
    }
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    if (m_models.empty())
    {
        return;
    }

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments pass the stencil test
    glStencilMask(0xFF); // enable writing to the stencil buffer


    for (const auto& model : m_models)
    {
        drawModel(m_shaderProgramTexture.value(), model);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);

        drawModel(m_shaderProgramSingleColor.value(), model, glm::scale(glm::vec3{ 1.05f,1.05f,1.05f }));

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);
    }
}

