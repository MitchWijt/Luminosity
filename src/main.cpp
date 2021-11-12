#include <iostream>

#include "Scene/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/Texture.hpp"
#include "Renderer/RenderApi.hpp"
#include "Entity/Entity.hpp"

#include "../editor/panels/ContentBrowserPanel.hpp"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

std::vector<Entity> entities;
bool createEntity = false;
bool isLight = false;


void CreateEntity()
{
	Entity entity = Entity(isLight);
	entities.push_back(entity);
	
	createEntity = false;
	isLight = false;
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
	
	Shaders entityShader = Shaders("Shaders/Object/VertexShader.glsl", "Shaders/Object/FragmentShader.glsl");
	Shaders lightShader = Shaders("Shaders/Lighting/VertexShader.glsl", "Shaders/Lighting/FragmentShader.glsl");

	RenderApi renderer = RenderApi();
						
    while(!glfwWindowShouldClose(window)) {
		processInput(window);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(createEntity)
		{
			CreateEntity();
			if(entities.size() == 1)
			{
				renderer.Create(entities[0].m_vertices);
			}
		}
		
		if(entities.size() > 0) {
			for(int i = 0; i < entities.size(); i++)
			{
				if(entities[i].m_hasLightComponent)
				{
					lightShader.Use();
					entities[i].SetMVPMatrix(lightShader);
					
					if(entities[i].m_orbitX)
						entities[i].OrbitX();
					if(entities[i].m_orbitY)
						entities[i].OrbitY();
					
					renderer.Draw();
					
					char posBuffer[30];
					sprintf(posBuffer, "dirLights[%d].position", i);
					
					char colorBuffer[30];
					sprintf(colorBuffer, "dirLights[%d].color", i);
					
					entityShader.Use();
					entityShader.Set3fUniform(posBuffer, entities[i].m_transform);
					entityShader.Set3fUniform(colorBuffer, entities[i].m_color);
				} else {
					entityShader.Use();
					entities[i].SetMVPMatrix(entityShader);
					entities[i].SetTexture(entityShader);
					
					
					renderer.Draw();
				}
				
				
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
				isLight = true;
				createEntity = true;
			}
			ImGui::EndMenu();
		}

		if(entities.size() > 0) {
			for(int i = 0; i < entities.size(); i++)
			{
				bool isLight = entities[i].m_hasLightComponent;

				ImGui::PushID(i);

				if(isLight)
				{
					ImGui::Text("Light %i", i);
					ImGui::Checkbox("OrbitX", &entities[i].m_orbitX);
					ImGui::Checkbox("OrbitY", &entities[i].m_orbitY);
					ImGui::SliderFloat3("Transform", (float*)&entities[i].m_transform, -10.0f, 10.0f);
					ImGui::ColorEdit3("Color", (float*)&entities[i].m_color);
				} else {
					ImGui::Text("Cube %i", i);
					ImGui::SliderFloat("Rotation Degrees", &entities[i].m_rotationDegrees, 0.0f, 360.0f);
					ImGui::Text("Rotation Axis");
					ImGui::Checkbox("X", &entities[i].m_rotateX);
					ImGui::Checkbox("Y", &entities[i].m_rotateY);
					ImGui::Checkbox("Z", &entities[i].m_rotateZ);
					ImGui::SliderFloat3("Transform", (float*)&entities[i].m_transform, -10.0f, 10.0f);
					ImGui::Text("Scale");
					ImGui::InputFloat3("Scaling", (float*)&entities[i].m_scale);
					ImGui::ColorEdit3("Color", (float*)&entities[i].m_color);
					
					ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
					if(ImGui::BeginDragDropTarget())
					{
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
						{
							const char* path = (const char*)payload->Data;
							
							Texture2D texture = Texture2D();
							texture.Create(path, ".jpeg");
							texture.Load();
							
							entities[i].textureID = texture.m_textureId;
						}
						ImGui::EndDragDropTarget();
					}
				}


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
