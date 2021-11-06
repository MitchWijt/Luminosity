#pragma once

#include "Entity.hpp"
#include "../Utils/Math.hpp"
#include "../Renderer/RenderApi.hpp"
#include "../Shaders/Shader.hpp"


std::vector<float> lightVertices {
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

class Light : public Entity {
public:
    Light()
    {
        renderer.Create(lightVertices);
        
        Light::transform = glm::vec3(0.0f, 0.0f, -8.0f);
        Light::rotateX = true;
        Light::rotateY = false;
        Light::rotateZ = false;
        Light::scale = glm::vec3(1.0f, 1.0f, 1.0f);
        Light::color = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    
    void Draw()
    {
        shader.Use();
        SetMVPMatrix();
        renderer.Draw();
    }
    
private:
    void SetMVPMatrix()
    {
        glm::mat4 scaleMatrix = GetScaleMatrix(Light::scale);
        glm::mat4 rotationMatrix = GetRotationMatrix(Light::rotationDegrees, glm::vec3((float)rotateX, (float)rotateY, (float)rotateZ));
        glm::mat4 modelMatrix =  rotationMatrix * scaleMatrix;
        shader.SetMatrix4fUniform("modelMatrix", modelMatrix);
        
        glm::mat4 viewMatrix = GetTranslationMatrix(Light::transform);
        shader.SetMatrix4fUniform("viewMatrix", viewMatrix);

        glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, 1200, 900, 0.1f, 100.0f);
        shader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);
    }
public:
    RenderApi renderer = RenderApi();
    Shaders shader = Shaders("Shaders/Lighting/VertexShader.glsl", "Shaders/Lighting/FragmentShader.glsl");
};
