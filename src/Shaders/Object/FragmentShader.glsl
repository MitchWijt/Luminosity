#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 ourColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightPos2;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse1 = diff * lightColor;
    
    vec3 lightDir2 = normalize(lightPos2 - fragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = diff2 * lightColor;
    
    vec3 diffuse = diffuse1 + diffuse2;
    
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 result = (ambient + diffuse) * ourColor;
    FragColor = texture(ourTexture, texCoord) * vec4(result, 1.0f);
}
