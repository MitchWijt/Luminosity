#include "Shader.hpp"

#include "../lheaders.hpp"
#include "../FileParser/FileParser.hpp"

Shaders::Shaders() {
    Shaders::m_vertexShaderSource = ParseContentsFromFilePath("Shaders/VertexShader.shader");
    Shaders::m_fragmentShaderSource = ParseContentsFromFilePath("Shaders/FragmentShader.shader");
}

unsigned int Shaders::CreateShaderProgram()
{
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, Shaders::m_vertexShaderSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, Shaders::m_fragmentShaderSource);
   
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    Shaders::m_programId = program;
    return program;
}

void Shaders::Set1FUniform(const GLchar* variable, float value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform1f(uniformLocation, value);
}

void Shaders::Set4fUniform(const GLchar* variable, glm::vec4 value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

unsigned int Shaders::CompileShader(unsigned int shaderType, std::string &shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
   
    const char* src = shaderSource.c_str();

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    return shader;
}