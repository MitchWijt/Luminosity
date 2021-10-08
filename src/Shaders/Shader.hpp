#pragma once
#include "../lheaders.hpp"
#include <iostream>

class Shaders
{
public:
    Shaders();
    unsigned int CreateShaderProgram();
    
    void Set1fUniform(const GLchar* variable, float value);
    void Set4fUniform(const GLchar* variable, glm::vec4 value);
    void Set1iUniform(const GLchar* variable, unsigned int value);
private:
    unsigned int CompileShader(unsigned int shaderType, std::string& shaderSource);
private:
    unsigned int m_programId;
    std::string m_vertexShaderSource;
    std::string m_fragmentShaderSource;
    std::string m_wavSource;
};


