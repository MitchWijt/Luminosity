#include <iostream>
#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"


void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    GLFWwindow* window = createWindow();
    
    float vertices[] = {
		1.0f, -0.5f, 0.0f,	1.0f, 0.0f, 1.0f,
		0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,
		
		-1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
	};
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	
	Shaders* shader = new Shaders();
	unsigned int shaderProgram = shader->CreateShaderProgram();
	
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return -1;
}
