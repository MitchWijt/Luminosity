#pragma once
#include <iostream>


struct TextureData {
    unsigned int width;
    unsigned int height;
    unsigned int colorType;
    unsigned char* data;
};

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    TextureData Create(const std::string& path, const std::string& extension);
    void Load(TextureData textureData);
    void Bind(unsigned int unit);
    void Unbind();
    
    
public:
    unsigned int m_colorType;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_textureId;
    unsigned char* m_data;
};
