#pragma once
#include <iostream>

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    void Load(const std::string& path, const std::string& extension);
    void Bind(unsigned int unit);
    void Unbind();
    
    
public:
    unsigned int m_textureId;
    unsigned char* m_data;
};
