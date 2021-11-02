#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = texture(ourTexture, texCoord) * vec4(result, 1.0f);
}
