#version 330 core

in vec4 ourColor;

out vec4 FragColor;

uniform vec4 uniformColor;

void main()
{
    FragColor = ourColor;
}
