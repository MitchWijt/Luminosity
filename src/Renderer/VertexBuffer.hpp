#pragma once
#include <vector>

class VertexBuffer
{
public:
    void Create(unsigned long size, std::vector<float>& vertices);
    void Bind();
    void SetData(unsigned long size, std::vector<float>& vertices);
    void SetAttribPointer(unsigned int location, unsigned int vertexCount, unsigned int stride, void* offset);
    
public:
    unsigned int m_VBO;
};

