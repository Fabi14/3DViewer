#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices)
{
    GLuint VBO{};
    glGenBuffers(1, &VBO);

    glBindVertexArray(*m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vecVertices), vecVertices.data(), GL_STATIC_DRAW); //Hint: Static Draw is set only once and used may times

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //Tells gpu how to interpret data
    glEnableVertexAttribArray(0);

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
