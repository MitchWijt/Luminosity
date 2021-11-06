#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Renderer/RenderApi.hpp"
#include "Entity/Cube.hpp"
#include "Entity/Light.hpp"

#include "../editor/panels/ContentBrowserPanel.hpp"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

std::vector<Cube> cubes;
std::vector<Light> lights;
bool createEntity = false;
bool createLight = false;

void CreateEntity()
{
	Cube cube = Cube();
	cubes.push_back(cube);
	
	createEntity = false;
}

void CreateLight()
{
	Light light = Light();
	lights.push_back(light);
	
	createLight = false;
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
		
		if(createLight)
			CreateLight();
		
		if(cubes.size() > 0) {
			for(int i = 0; i < cubes.size(); i++)
			{
				cubes[i].Draw();
			}
		}
		
		if(lights.size() > 0) {
			for(int i = 0; i < lights.size(); i++)
			{
				float lightX = 2.0f * sin(glfwGetTime());
				float lightY = lights[i].transform.y;
				float lightZ = -8.0f + cos(glfwGetTime());

				lights[i].transform = glm::vec3(lightX, lightY, lightZ);
				lights[i].Draw();
			}
		}
						
		//UI
		ImGui::Begin("Sidebar");
		
		if(ImGui::BeginMenu("Create"))
		{
			if(ImGui::MenuItem("Entity"))
			{
				createEntity = true;
			}
			if(ImGui::MenuItem("Light"))
			{
				createLight = true;
			}
			
			ImGui::EndMenu();
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
		
		if(lights.size() > 0) {
			for(int i = 0; i < lights.size(); i++)
			{
				ImGui::PushID(i + 1);
				ImGui::Text("Cube %i", i);
				ImGui::SliderFloat("Rotation Degrees", &lights[i].rotationDegrees, 0.0f, 360.0f);
				ImGui::Text("Rotation Axis");
				ImGui::Checkbox("X", &lights[i].rotateX);
				ImGui::Checkbox("Y", &lights[i].rotateY);
				ImGui::Checkbox("Z", &lights[i].rotateZ);
				ImGui::SliderFloat3("Transform", (float*)&lights[i].transform, -10.0f, 10.0f);
				ImGui::Text("Scale");
				ImGui::InputFloat3("Scaling", (float*)&lights[i].scale);
				ImGui::ColorEdit3("Color", (float*)&lights[i].color);
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
