#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Utils/Math.hpp"
#include "Utils/AssetManager.hpp"
#include "Renderer/RenderApi.hpp"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"


struct GameLoopVariables {
	bool rotateX = true;
	bool rotateY;
	bool rotateZ;
	float xPos;
	float yPos;
	float zPos = -3.0f;
	float rotationDegrees;
	float offsetX;
	int windowWidth = 1200;
	int windowHeight = 900;
	bool texture1Checked;
	bool texture2Checked;
	float ourColors[3]{1.0f, 1.0f, 1.0f};
	std::string texturePath = "../assets/brickwall.jpeg";
};

struct GameLoopVariables gameVariables;

void window_size_callback(GLFWwindow* window, int width, int height)
{
	gameVariables.windowWidth = width;
	gameVariables.windowHeight = height;
}

void processInput(GLFWwindow* window, Shaders shader)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    GLFWwindow* window = createWindow();
	
	RenderApi renderer = RenderApi();
	renderer.CreateCube();
	
	Shaders shader = Shaders();
	unsigned int shaderProgram = shader.CreateShaderProgram();
	
	Texture2D texture = Texture2D();
	texture.Load(gameVariables.texturePath, ".jpeg");
	
	glUseProgram(shaderProgram);
	shader.Set1iUniform("ourTexture", 0);
	
	AssetManager assets = AssetManager("../assets");
					
    while(!glfwWindowShouldClose(window)) {
		processInput(window, shader);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		glfwSetWindowSizeCallback(window, window_size_callback);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		
		texture.Bind(GL_TEXTURE0);
				
		glm::mat4 modelMatrix = GetRotationMatrix(gameVariables.rotationDegrees, glm::vec3((float)gameVariables.rotateX, (float)gameVariables.rotateY, (float)gameVariables.rotateZ));
		shader.SetMatrix4fUniform("modelMatrix", modelMatrix);
		
		glm::mat4 viewMatrix = GetTranslationMatrix(glm::vec3(gameVariables.xPos - 1.0, gameVariables.yPos, gameVariables.zPos));
		shader.SetMatrix4fUniform("viewMatrix", viewMatrix);
		
		glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, gameVariables.windowWidth, gameVariables.windowHeight, 0.1f, 100.0f);
		shader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);
		
		shader.Set3fUniform("ourColor", glm::vec3(gameVariables.ourColors[0], gameVariables.ourColors[1], gameVariables.ourColors[2]));
		
		renderer.DrawCube();
		
		
		glm::mat4 viewMatrix2 = GetTranslationMatrix(glm::vec3(gameVariables.xPos + 1.0, gameVariables.yPos, gameVariables.zPos));
		shader.SetMatrix4fUniform("viewMatrix", viewMatrix2);
		renderer.DrawCube();
	
		ImGui::Begin("Sidebar");
		ImGui::Text("Rotation Degrees");
		ImGui::SliderFloat("", &gameVariables.rotationDegrees, 0.0f, 360.0f);
		ImGui::Text("Rotation Axis");
		ImGui::Checkbox("X", &gameVariables.rotateX);
		ImGui::Checkbox("Y", &gameVariables.rotateY);
		ImGui::Checkbox("Z", &gameVariables.rotateZ);
		
		ImGui::SliderFloat("X Pos", &gameVariables.xPos, -10.0f, 10.0f);
		ImGui::SliderFloat("Y Pos", &gameVariables.yPos, -10.0f, 10.0f);
		ImGui::SliderFloat("Z Pos", &gameVariables.zPos, -10.0f, 10.0f);
		
		ImGui::ColorEdit3("Color", (float*)&gameVariables.ourColors);
		
		ImGui::End();
		
		ImGui::Begin("Textures");
		ImGui::BeginChild("Scrolling");
		ImGui::Text("Texture");
		for (int i = 0; i < assets.m_filePaths.size(); i++)
		{
			std::string fileExtension = assets.m_filePaths[i].extension;
			std::string filePath = assets.m_filePaths[i].filePath;
			std::string fileName = assets.m_filePaths[i].fileName;
			if(ImGui::Button(fileName.c_str()))
			{
				texture.Load(filePath, fileExtension);
				texture.Bind(GL_TEXTURE0);
			}
		};
		ImGui::EndChild();
		ImGui::End();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    glfwTerminate();
    return -1;
}
