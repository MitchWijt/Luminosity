#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool hasLightComponent;

void main()
{
    if(!hasLightComponent) {
        texCoord = aTexCoord;
        normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
        fragPos = vec3(viewMatrix * modelMatrix * vec4(aPos, 1.0));
    }
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}
