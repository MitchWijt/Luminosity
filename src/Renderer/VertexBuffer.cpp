#include "VertexBuffer.hpp"
#include "../lheaders.hpp"

void VertexBuffer::Create(unsigned int size, void* vertices)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    VertexBuffer::m_VBO = vboID;
    
    VertexBuffer::Bind();
    VertexBuffer::SetData(size, vertices);
    VertexBuffer::SetAttribPointer(0, 3, 5 * sizeof(float), (void*)0);
    VertexBuffer::SetAttribPointer(1, 3, 5 * sizeof(float), (void*) (3 * sizeof(float)));
};

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
};

void VertexBuffer::SetData(unsigned int size, void* vertices)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
};

void VertexBuffer::SetAttribPointer(unsigned int location, unsigned int vertexCount, unsigned int stride, void *offset)
{
    glVertexAttribPointer(location, vertexCount, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
};
        

