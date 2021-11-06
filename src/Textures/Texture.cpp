#include "../lheaders.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb_image.hpp"
#include "Texture.hpp"


Texture2D::Texture2D()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Texture2D::m_textureId = texture;
}

//Texture2D::~Texture2D() {
//    stbi_image_free(Texture2D::m_data);
//}

void Texture2D::Load(const std::string& path, const std::string& extension)
{
    int width;
    int height;
    int nrChannels;
    
    unsigned int colorType = extension == ".jpeg" || extension == ".jpg" ? GL_RGB : GL_RGBA;

//    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    if(!data)
        std::cout << "Failed to load texture at path: " << path << std::endl;
    
    Texture2D::m_data = data;
    Texture2D::m_width = width;
    Texture2D::m_height = height;
    
    glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture2D::Bind(unsigned int unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, Texture2D::m_textureId);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
