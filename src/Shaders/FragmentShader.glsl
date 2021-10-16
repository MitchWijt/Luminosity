#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 ourColor;

void main()
{
    FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0f);
}
