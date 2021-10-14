#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Utils/Math.hpp"



float offsetX = 0.0f;

void processInput(GLFWwindow* window, Shaders shader)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		offsetX += 0.01f;
		shader.Set1fUniform("offsetX", offsetX);
	}
	
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		offsetX -= 0.01f;
		shader.Set1fUniform("offsetX", offsetX);
	}
}

int main() {
    GLFWwindow* window = createWindow();
	
    float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	
	Shaders shader = Shaders();
	unsigned int shaderProgram = shader.CreateShaderProgram();
	
	Texture2D texture1 = Texture2D();
	texture1.Load("../images/brickwall.jpeg", GL_RGB);
	
	Texture2D texture2 = Texture2D();
	texture2.Load("../images/defqon.png", GL_RGBA);
	
	glUseProgram(shaderProgram);
	shader.Set1iUniform("ourTexture1", 0);
	shader.Set1iUniform("ourTexture2", 1);
		
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window, shader);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		
		
		texture1.Bind(GL_TEXTURE0);
		texture2.Bind(GL_TEXTURE1);
		
		float time = glfwGetTime();
		
		glm::mat4 modelMatrix = GetRotationMatrix(time * 20, glm::vec3(0.5f, 1.0f, 0.0f));
		shader.SetMatrix4fUniform("modelMatrix", modelMatrix);
		
		glm::mat4 viewMatrix = GetTranslationMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
		shader.SetMatrix4fUniform("viewMatrix", viewMatrix);
		
		glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);
		shader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);
		
		glBindVertexArray(VAO);
		for(int i = 0; i <= 10; i++)
		{
			glm::mat4 viewMatrix = GetTranslationMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
			shader.SetMatrix4fUniform("viewMatrix", viewMatrix);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return -1;
}
