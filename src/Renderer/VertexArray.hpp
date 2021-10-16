#pragma once

class VertexArray
{
public:
    void Create();
    void Bind();
    void Unbind();
public:
    unsigned int m_VAO;
};
