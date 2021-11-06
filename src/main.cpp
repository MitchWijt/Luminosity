#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Renderer/RenderApi.hpp"
#include "Entity/Cube.hpp"

#include "../editor/panels/ContentBrowserPanel.hpp"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

std::vector<Cube> cubes;
bool createEntity = false;

void CreateEntity()
{
	Cube cube = Cube();
	cubes.push_back(cube);
	
	createEntity = false;
}

//void window_size_callback(GLFWwindow* window, int width, int height)
//{
//	gameVariables.windowWidth = width;
//	gameVariables.windowHeight = height;
//}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    GLFWwindow* window = createWindow();
	ContentBrowserPanel contentBrowser = ContentBrowserPanel();
					
    while(!glfwWindowShouldClose(window)) {
		processInput(window);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(createEntity)
			CreateEntity();
		
		
//		float lightX = gameVariables.lightRadius * sin(glfwGetTime());
//		float lightY = gameVariables.yPos;
//		float lightZ = gameVariables.zPos + cos(glfwGetTime());
//
//		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
//
//		float lightX2 = 0.0f;
//		float lightY2 = cos(glfwGetTime());
//		float lightZ2 = gameVariables.zPos + (gameVariables.lightRadius * sin(glfwGetTime()));
//		glm::vec3 lightPos2 = glm::vec3(lightX2, lightY2, lightZ2);
		
		if(cubes.size() > 0) {
			for(int i = 0; i < cubes.size(); i++)
			{
				cubes[i].Draw();
			}
		}
				
		//Light 1
//		lightingShader.Use();
//
//		glm::mat4 modelMatrixLight = GetScaleMatrix(glm::vec3(0.2, 0.2, 0.2));
//		lightingShader.SetMatrix4fUniform("modelMatrix", modelMatrixLight);
//
//		glm::mat4 viewMatrixLight = GetTranslationMatrix(lightPos);
//		lightingShader.SetMatrix4fUniform("viewMatrix", viewMatrixLight);
//
//		glm::mat4 projectionMatrixLight = GetProjectionMatrix(45.0f, gameVariables.windowWidth, gameVariables.windowHeight, 0.1f, 100.0f);
//		lightingShader.SetMatrix4fUniform("projectionMatrix", projectionMatrixLight);
//
//		lightSourceRenderer.DrawCube();
		
		//Light 2
//		lightingShader.Use();
//
//		glm::mat4 viewMatrixLight2 = GetTranslationMatrix(lightPos2);
//		lightingShader.SetMatrix4fUniform("viewMatrix", viewMatrixLight2);
//
//		lightSourceRenderer.DrawCube();
		
		//UI
		ImGui::Begin("Sidebar");
				
		if(ImGui::Button("Create Entity")){
			createEntity = true;
		}
		
		if(cubes.size() > 0) {
			for(int i = 0; i < cubes.size(); i++)
			{
				ImGui::PushID(i);
				ImGui::Text("Cube %i", i);
				ImGui::SliderFloat("Rotation Degrees", &cubes[i].rotationDegrees, 0.0f, 360.0f);
				ImGui::Text("Rotation Axis");
				ImGui::Checkbox("X", &cubes[i].rotateX);
				ImGui::Checkbox("Y", &cubes[i].rotateY);
				ImGui::Checkbox("Z", &cubes[i].rotateZ);
				ImGui::SliderFloat3("Transform", (float*)&cubes[i].transform, -10.0f, 10.0f);
				ImGui::Text("Scale");
				ImGui::InputFloat3("Scaling", (float*)&cubes[i].scale);
				ImGui::ColorEdit3("Color", (float*)&cubes[i].color);
				ImGui::PopID();
			}
		}
		
		ImGui::End();
		
		contentBrowser.OnImGuiRender();
		
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
