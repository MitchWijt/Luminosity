#pragma once

#include "VertexArray.hpp"

class RenderApi
{
public:
    RenderApi();
    void CreateCube();
    void DrawCube();
    
public:
    VertexArray m_vertexArray;
};
