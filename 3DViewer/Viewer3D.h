#pragma once
#include "Engine.h"

#include "Camera.h"
#include "Model.h"

class Viewer3D : public Engine
{
	void onCreate() override;
    void onUpdate(double deltaTime) override;

private:
    void initModels();
    void handleInput(double deltaTime);
    void draw();


    std::vector<Model> m_models{};


    Camera m_camera;

    bool m_firstMouse{ true };
    glm::vec2 m_lastMousePos;
};

