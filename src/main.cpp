#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Utils/Math.hpp"
#include "Renderer/RenderApi.hpp"

#include "../editor/panels/ContentBrowserPanel.hpp"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"


struct GameLoopVariables {
	bool rotateX = true;
	bool rotateY;
	bool rotateZ;
	float xPos;
	float yPos;
	float zPos = -8.0f;
	float rotationDegrees;
	float offsetX;
	int windowWidth = 1200;
	int windowHeight = 900;
	bool texture1Checked;
	bool texture2Checked;
	float ourColors[3]{1.0f, 1.0f, 1.0f};
	float lightRadius = 2.0f;
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
	
	RenderApi objectRenderer = RenderApi();
	objectRenderer.CreateCube();
	
	RenderApi lightSourceRenderer = RenderApi();
	lightSourceRenderer.CreateCube();
		
	Shaders objectShader = Shaders("Shaders/Object/VertexShader.glsl", "Shaders/Object/FragmentShader.glsl");
	objectShader.Use();
	
	Shaders lightingShader = Shaders("Shaders/Lighting/VertexShader.glsl", "Shaders/Lighting/FragmentShader.glsl");
	lightingShader.Use();
	
	Texture2D texture = Texture2D();
	texture.Load(gameVariables.texturePath, ".jpeg");
		
	objectShader.Set1iUniform("ourTexture", 0);
	
	ContentBrowserPanel contentBrowser = ContentBrowserPanel();
					
    while(!glfwWindowShouldClose(window)) {
		processInput(window, objectShader);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		glfwSetWindowSizeCallback(window, window_size_callback);
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		texture.Bind(GL_TEXTURE0);
		
		float lightX = gameVariables.lightRadius * sin(glfwGetTime());
		float lightY = gameVariables.yPos;
		float lightZ = gameVariables.zPos + cos(glfwGetTime()); 
		
		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
		
		float lightX2 = 0.0f;
		float lightY2 = cos(glfwGetTime());
		float lightZ2 = gameVariables.zPos + (gameVariables.lightRadius * sin(glfwGetTime()));
		glm::vec3 lightPos2 = glm::vec3(lightX2, lightY2, lightZ2);
		
		//Object
		objectShader.Use();
		objectShader.Set3fUniform("lightPos", lightPos);
		objectShader.Set3fUniform("lightPos2", lightPos2);
		objectShader.Set3fUniform("lightColor", glm::vec3(1.0, 1.0, 1.0));

		glm::mat4 modelMatrix = GetRotationMatrix(gameVariables.rotationDegrees, glm::vec3((float)gameVariables.rotateX, (float)gameVariables.rotateY, (float)gameVariables.rotateZ));
		objectShader.SetMatrix4fUniform("modelMatrix", modelMatrix);

		glm::mat4 viewMatrix = GetTranslationMatrix(glm::vec3(gameVariables.xPos, gameVariables.yPos, gameVariables.zPos));
		objectShader.SetMatrix4fUniform("viewMatrix", viewMatrix);

		glm::mat4 projectionMatrix = GetProjectionMatrix(45.0f, gameVariables.windowWidth, gameVariables.windowHeight, 0.1f, 100.0f);
		objectShader.SetMatrix4fUniform("projectionMatrix", projectionMatrix);

		objectShader.Set3fUniform("ourColor", glm::vec3(gameVariables.ourColors[0], gameVariables.ourColors[1], gameVariables.ourColors[2]));

		objectRenderer.DrawCube();
		
		//Light 1
		lightingShader.Use();
		
		glm::mat4 modelMatrixLight = GetScaleMatrix(glm::vec3(0.2, 0.2, 0.2));
		lightingShader.SetMatrix4fUniform("modelMatrix", modelMatrixLight);
		
		glm::mat4 viewMatrixLight = GetTranslationMatrix(lightPos);
		lightingShader.SetMatrix4fUniform("viewMatrix", viewMatrixLight);
		
		glm::mat4 projectionMatrixLight = GetProjectionMatrix(45.0f, gameVariables.windowWidth, gameVariables.windowHeight, 0.1f, 100.0f);
		lightingShader.SetMatrix4fUniform("projectionMatrix", projectionMatrixLight);
		
		lightSourceRenderer.DrawCube();
		
		//Light 2
		lightingShader.Use();
		
		glm::mat4 viewMatrixLight2 = GetTranslationMatrix(lightPos2);
		lightingShader.SetMatrix4fUniform("viewMatrix", viewMatrixLight2);
		
		lightSourceRenderer.DrawCube();
		
		//UI
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
		
		ImGui::SliderFloat("Light Radius", &gameVariables.lightRadius, -10.0f, 10.0f);
		
		ImGui::ColorEdit3("Color", (float*)&gameVariables.ourColors);
		
		ImGui::End();
		
		contentBrowser.OnImGuiRender(&texture);
		
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
