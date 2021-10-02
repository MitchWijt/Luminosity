#pragma once

#include <iostream>
#include "../lheaders.hpp"

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
    
    std::string m_vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   ourColor = vec4(aColor, 1.0);\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    
    std::string m_fragmentShaderSource = "#version 330 core\n"
        "in vec4 ourColor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\0";
};


