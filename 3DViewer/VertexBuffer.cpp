#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices)
{
    GLuint VBO{};
    glGenBuffers(1, &VBO);

    glBindVertexArray(*m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vecVertices.size() * sizeof(Vertex), vecVertices.data(), GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0)); //pos
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3))); //col

    glBindVertexArray(0);
}

void VertexBuffer::bind()
{
    glBindVertexArray(*m_vao);
}

GLuint VertexBuffer::createVao()
{
    GLuint VAO{};
    glGenVertexArrays(1, &VAO);
    return VAO;
}

void VertexBuffer::deleteVao(GLuint id)
{
    glDeleteVertexArrays(1, &id);
}
