#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourColor;
uniform float offsetX;

void main()
{
    ourColor = vec4(aColor, 1.0);
    gl_Position = vec4(aPos.x + offsetX, aPos.y, aPos.z, 1.0);
}
