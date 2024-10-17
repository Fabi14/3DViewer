#pragma once
#include "Engine.h"

#include "Camera.h"
#include "Model.h"
#include "Skybox.h"

class Viewer3D : public Engine
{
	void onCreate() override;
    void onUpdate(double deltaTime) override;

private:
    void initModels();
    void handleInput(double deltaTime);
    void drawModel(ShaderProgram& shader, const Model& model, const glm::mat4& mat = glm::mat4{ 1.f });
    void draw();


    std::vector<Model> m_models{};
    std::optional<ShaderProgram> m_shaderProgramSingleColor;
    std::optional<ShaderProgram> m_shaderProgramTexture;

    std::optional<Skybox> m_skybox;

    Camera m_camera;

    bool m_firstMouse{ true };
    glm::vec2 m_lastMousePos;
}; 

