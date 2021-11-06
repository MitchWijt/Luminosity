#pragma once

#include "VertexArray.hpp"
#include <vector>

class RenderApi
{
public:
    RenderApi();
    void Create(std::vector<float>& vertices);
    void Draw();
    
public:
    VertexArray m_vertexArray;
};
