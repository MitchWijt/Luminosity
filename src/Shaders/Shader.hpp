#pragma once
#include "../FileParser/FileParser.hpp"

class Shaders
{
public:
    unsigned int CreateShaderProgram()
    {
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, m_vertexShaderSource);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_fragmentShaderSource);
        
        unsigned int program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        return program;
    }
private:
    unsigned int CompileShader(unsigned int shaderType, std::string& shaderSource)
    {
        unsigned int shader = glCreateShader(shaderType);
        
        const char* src = shaderSource.c_str();
        
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);
        
        return shader;
    }
private:
    std::string m_vertexShaderSource = ParseContentsFromFilePath("Shaders/VertexShader.shader");
    std::string m_fragmentShaderSource = ParseContentsFromFilePath("Shaders/FragmentShader.shader");
};


