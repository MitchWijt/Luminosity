#pragma once

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    void Load(const char* path, unsigned int colorType);
    void Bind(unsigned int unit);
    void Unbind();
    
    
public:
    unsigned int m_textureId;
    unsigned char* m_data;
};
