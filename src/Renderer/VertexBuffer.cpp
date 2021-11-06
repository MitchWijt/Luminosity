#include "VertexBuffer.hpp"
#include "../lheaders.hpp"

void VertexBuffer::Create(unsigned long size, std::vector<float>& vertices)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    VertexBuffer::m_VBO = vboID;
    
    VertexBuffer::Bind();
    VertexBuffer::SetData(size, vertices);
    VertexBuffer::SetAttribPointer(0, 3, 8 * sizeof(float), (void*)0);
    VertexBuffer::SetAttribPointer(1, 2, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    VertexBuffer::SetAttribPointer(2, 3, 8 * sizeof(float), (void*) (5 * sizeof(float)));
};

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
};

void VertexBuffer::SetData(unsigned long size, std::vector<float>& vertices)
{
    glBufferData(GL_ARRAY_BUFFER, size, static_cast<void*>(vertices.data()), GL_STATIC_DRAW);
};

void VertexBuffer::SetAttribPointer(unsigned int location, unsigned int vertexCount, unsigned int stride, void *offset)
{
    glVertexAttribPointer(location, vertexCount, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
};
        

