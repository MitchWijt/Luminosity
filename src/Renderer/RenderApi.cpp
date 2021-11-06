#include "../lheaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "RenderApi.hpp"

RenderApi::RenderApi()
{
    VertexArray vertexArray = VertexArray();
    vertexArray.Create();
    vertexArray.Bind();
    
    RenderApi::m_vertexArray = vertexArray;
}

void RenderApi::Create(std::vector<float>& vertices)
{

    VertexBuffer vertexBuffer = VertexBuffer();
    vertexBuffer.Create(vertices.size() * sizeof(vertices[0]), vertices);
}
 
void RenderApi::Draw()
{
    RenderApi::m_vertexArray.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
    

