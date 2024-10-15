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
        glEnableVertexAttribArray(static_cast<GLuint>(i));
        glVertexAttribPointer(static_cast<GLuint>(i), attr.m_size, attr.m_type, attr.m_normalized, attr.m_stride, attr.m_pointer);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices) :
//    VertexBuffer(vecVertices)
//{
//
//}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vecVertices, const std::vector<Index>& vecIndices, const std::vector<InstanceData>& vecInstanceData) :
    VertexBuffer(vecVertices)
{
    m_indexCount = static_cast<GLsizei>(vecIndices.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(Index), vecIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_instanceCount = static_cast<GLsizei>(vecInstanceData.size());
    glBindBuffer(GL_ARRAY_BUFFER, *m_instanceVbo);
    glBufferData(GL_ARRAY_BUFFER, vecInstanceData.size() * sizeof(InstanceData), vecInstanceData.data(), GL_STATIC_DRAW);

    
    auto layout = InstanceData::getLayout();
    auto offset = Vertex::getLayout().m_vecAttributs.size();

    for (const auto&& [i, attr] : std::views::enumerate(layout.m_vecAttributs))
    {
        glEnableVertexAttribArray(static_cast<GLuint>(i+ offset));
        glVertexAttribPointer(static_cast<GLuint>(i+ offset), attr.m_size, attr.m_type, attr.m_normalized, attr.m_stride, attr.m_pointer);
        glVertexAttribDivisor(static_cast<GLuint>(i + offset), 1);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *m_instanceVbo);
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
