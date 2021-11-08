#pragma once

#include "../Utils/Math.hpp"
#include "../Renderer/RenderApi.hpp"
#include "../Shaders/Shader.hpp"
#include "../Textures/Texture.hpp"


std::vector<float> vertices {
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,     1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,

    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f
};

class Entity {
public:
    Entity(bool isLight)
    {
        m_vertices = vertices;
        m_transform = glm::vec3(0.0f, 0.0f, -8.0f);
        m_rotateX = true;
        m_rotateY = false;
        m_rotateZ = false;
        m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
        m_color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_rotationDegrees = 0.0f;
        
        if(isLight)
        {
            m_hasLightComponent = true;
            m_scale = glm::vec3(0.2f, 0.2f, 0.2f);
        }
           
    }
    
//    void SetTexture(const std::string& path)
//    {
//        texture.Load(path, ".jpeg");
//        shader.Set1iUniform("ourTexture", 0);
//        texture.Bind(GL_TEXTURE0);
//    }
    
    void OrbitX()
    {
        float xPos = 2.0f * sin(glfwGetTime());
        float yPos = 0.0f;
        float zPos = -8.0f + cos(glfwGetTime());

        m_transform = glm::vec3(xPos, yPos, zPos);
    }
    
    void OrbitY()
    {
        float xPos = 0.0f;
        float yPos = cos(glfwGetTime());
        float zPos = -8.0f + sin(glfwGetTime());

        m_transform = glm::vec3(xPos, yPos, zPos);
    }
    
    void SetMVPMatrix(Shaders shader)
    {
        shader.Set3fUniform("ourColor", m_color);
        
        glm::mat4 scaleMatrix = GetScaleMatrix(m_scale);
        glm::mat4 rotationMatrix = GetRotationMatrix(m_rotationDegrees, glm::vec3((float)m_rotateX, (float)m_rotateY, (float)m_rotateZ));
        glm::mat4 modelMatrix =  rotationMatrix * scaleMatrix;
        shader.SetMatrix4fUniform("modelMatrix", modelMatrix);
        
        glm::mat4 viewMatrix = GetTranslationMatrix(m_transform);
        shader.SetMatrix4fUniform("viewMatrix", viewMatrix);

        glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, 1200, 900, 0.1f, 100.0f);
        shader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);
    }
    
public:
    glm::vec3 m_transform;
    glm::vec3 m_scale;
    glm::vec3 m_color;
    bool m_rotateX;
    bool m_rotateY;
    bool m_rotateZ;
    bool m_hasLightComponent = false;
    float m_rotationDegrees;
    bool m_orbitX = false;
    bool m_orbitY = false;
    std::string m_texturePath;
    std::vector<float> m_vertices;
    Texture2D texture = Texture2D();
};
