#pragma once
#include "../lheaders.hpp"
#include <iostream>

class Shaders
{
public:
    Shaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    unsigned int CreateShaderProgram();
    void Use();
    
    void Set1fUniform(const GLchar* variable, float value);
    void Set4fUniform(const GLchar* variable, glm::vec4 value);
    void Set3fUniform(const GLchar* variable, glm::vec3 value);
    void Set1iUniform(const GLchar* variable, unsigned int value);
    void SetVec3(const GLchar* variable, glm::vec3 value);
    void SetMatrix4fUniform(const GLchar* variable, glm::mat4 value);
private:
    unsigned int CompileShader(unsigned int shaderType, std::string& shaderSource);
private:
    unsigned int m_programId;
    std::string m_vertexShaderSource;
    std::string m_fragmentShaderSource;
    std::string m_wavSource;
};


