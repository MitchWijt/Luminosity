#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = texture(ourTexture, texCoord) * vec4(lightColor * objectColor, 1.0f);
}
