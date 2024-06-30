#pragma once
#include "Engine.h"

class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate() override;

    void initTriangles();
    void draw();

    struct Triangle
    {
        ShaderProgram m_shaderProgram;
        VertexBuffer m_vertexBuffer;
    };
    std::optional<Triangle> m_triangle{ std::nullopt };
};

