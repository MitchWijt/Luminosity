#include "VertexArray.hpp"
#include "../lheaders.hpp"

void VertexArray::Create()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    VertexArray::m_VAO = vaoID;
}

void VertexArray::Bind()
{
    glBindVertexArray(VertexArray::m_VAO);
}
    
void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
