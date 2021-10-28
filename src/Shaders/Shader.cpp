#include "Shader.hpp"

#include "../lheaders.hpp"
#include "../FileParser/FileParser.hpp"

Shaders::Shaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    Shaders::m_vertexShaderSource = ParseContentsFromFilePath(vertexShaderPath.c_str());
    Shaders::m_fragmentShaderSource = ParseContentsFromFilePath(fragmentShaderPath.c_str());
    CreateShaderProgram();
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

void Shaders::Use()
{
    glUseProgram(m_programId);
}

void Shaders::Set1fUniform(const GLchar* variable, float value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform1f(uniformLocation, value);
}

void Shaders::Set4fUniform(const GLchar* variable, glm::vec4 value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

void Shaders::Set3fUniform(const GLchar* variable, glm::vec3 value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}


void Shaders::Set1iUniform(const GLchar* variable, unsigned int value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniform1i(uniformLocation, value);
}

void Shaders::SetMatrix4fUniform(const GLchar* variable, glm::mat4 value)
{
    int uniformLocation = glGetUniformLocation(Shaders::m_programId, variable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shaders::CompileShader(unsigned int shaderType, std::string &shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
   
    const char* src = shaderSource.c_str();

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    return shader;
}
