#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static glm::mat4 GetRotationMatrix(float degrees, glm::vec3 axis)
{
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::rotate(transformation, glm::radians(degrees), axis);
    
    return transformation;
}

static glm::mat4 GetScaleMatrix(glm::vec3 scaleVector)
{
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::scale(transformation, scaleVector);
    
    return transformation;
}

static glm::mat4 GetTranslationMatrix(glm::vec3 translationVector)
{
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, translationVector);
    
    return transformation;
}

static glm::mat4 GetProjectionMatrix(float fov, float width, float height, float near, float far)
{
    float aspectRatio = width / height;
    glm::mat4 projection = glm::perspective(fov, aspectRatio, near, far);
    
    return projection;
}
