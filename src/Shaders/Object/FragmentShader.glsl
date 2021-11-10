
#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 ourColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

struct DirLight {
    vec3 position;
    vec3 color;
};

uniform DirLight dirLights[20];
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos);

void main()
{
    vec3 norm = normalize(normal);
    vec3 result = CalcDirLight(dirLights[0], norm, fragPos) * ourColor;
    
    for(int i = 0; i < 20; i++)
    {
        result += (CalcDirLight(dirLights[i + 1], norm, fragPos) * ourColor);
    }
    
    FragColor = texture(ourTexture, texCoord) + vec4(result, 1.0f);
    
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;
    
    return (ambient + diffuse);
}
