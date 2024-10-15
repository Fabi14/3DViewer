#include "VertexBuffer.h"
#include <glad/glad.h>
#include <ranges>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vecVertices.size() * sizeof(Vertex), vecVertices.data(), GL_STATIC_DRAW); 


    auto layout = Vertex::getLayout();

    for (const auto&& [i,attr] : std::views::enumerate(layout.m_vecAttributs))
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attr.m_size, attr.m_type, attr.m_normalized, attr.m_stride, attr.m_pointer); 
    }

    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0)); //pos
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3))); //col
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3) + sizeof(glm::vec4))); //norm

    //glEnableVertexAttribArray(3);
    //glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices) :
    VertexBuffer(vecVertices)
{
    m_indexCount = static_cast<GLsizei>(vecIndices.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(Index), vecIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
}

GLuint VertexBuffer::createVao()
{
    GLuint VAO{};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    return VAO;
}

GLuint VertexBuffer::createBuffer()
{
    GLuint vbo{};
    glGenBuffers(1, &vbo);
    return vbo;
}

void VertexBuffer::deleteVao(GLuint id)
{
    glDeleteVertexArrays(1, &id);
}

void VertexBuffer::deleteBuffer(GLuint id)
{
    glDeleteBuffers(1, &id);
}
