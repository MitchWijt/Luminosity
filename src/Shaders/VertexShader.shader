#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform float offsetX;

void main()
{
    texCoord = aTexCoord;
    ourColor = vec4(aColor, 1.0);
    gl_Position = vec4(aPos.x + offsetX, aPos.y, aPos.z, 1.0);
}
