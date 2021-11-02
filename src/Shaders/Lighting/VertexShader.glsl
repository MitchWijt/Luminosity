#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrixL;
uniform mat4 viewMatrixL;
uniform mat4 projectionMatrixL;

void main()
{
    gl_Position = projectionMatrixL * viewMatrixL * modelMatrixL * vec4(aPos, 1.0);
}
