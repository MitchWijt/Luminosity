#pragma once

class VertexBuffer
{
public:
    void Create(unsigned int size, void* vertices);
    void Bind();
    void SetData(unsigned int size, void* vertices);
    void SetAttribPointer(unsigned int location, unsigned int vertexCount, unsigned int stride, void* offset);
    
public:
    unsigned int m_VBO;
};

