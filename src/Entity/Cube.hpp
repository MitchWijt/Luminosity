#pragma once

#include "Entity.hpp"
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

class Cube : public Entity {
public:
    Cube()
    {
        renderer.Create(vertices);
        
        Cube::transform = glm::vec3(0.0f, 0.0f, -8.0f);
        Cube::rotateX = true;
        Cube::rotateY = false;
        Cube::rotateZ = false;
        Cube::scale = glm::vec3(1.0f, 1.0f, 1.0f);
        Cube::color = glm::vec3(1.0f, 1.0f, 1.0f);
        Cube::texturePath = "../assets/brickwall.jpeg";
        
        LoadTexture();
    }
    
    void Draw()
    {
        shader.Use();
        BindTexture();
        SetMVPMatrix();
        renderer.Draw();
    }
    
    void LoadTexture()
    {
        texture.Load(texturePath, ".jpeg");
        shader.Set1iUniform("ourTexture", 0);

    }
    
    void BindTexture()
    {
        texture.Bind(GL_TEXTURE0);
    }
    
private:
    void SetMVPMatrix()
    {
        shader.Set3fUniform("ourColor", Cube::color);
        
        glm::mat4 scaleMatrix = GetScaleMatrix(Cube::scale);
        glm::mat4 rotationMatrix = GetRotationMatrix(Cube::rotationDegrees, glm::vec3((float)rotateX, (float)rotateY, (float)rotateZ));
        glm::mat4 modelMatrix =  rotationMatrix * scaleMatrix;
        shader.SetMatrix4fUniform("modelMatrix", modelMatrix);
        
        glm::mat4 viewMatrix = GetTranslationMatrix(Cube::transform);
        shader.SetMatrix4fUniform("viewMatrix", viewMatrix);

        glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, 1200, 900, 0.1f, 100.0f);
        shader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);
    }
public:
    Texture2D texture = Texture2D();
    RenderApi renderer = RenderApi();
    Shaders shader = Shaders("Shaders/Object/VertexShader.glsl", "Shaders/Object/FragmentShader.glsl");
};
