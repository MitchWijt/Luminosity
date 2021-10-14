#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    FragColor = mix(texture(ourTexture1, texCoord), texture(ourTexture2, texCoord), 0.5);
}
