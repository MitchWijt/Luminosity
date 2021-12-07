#pragma once
#include <iostream>
#include <vector>

#include "../lheaders.hpp"

#include "../Shaders/Shader.hpp"
#include "../Application.hpp"
#include "../Textures/Texture.hpp"
#include "../Entity/Entity.hpp"
#include "../Renderer/RenderApi.hpp"

#include "../../editor/panels/ContentBrowserPanel.hpp"

#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_glfw.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"


struct SceneFlags
{
    bool entityIsLight = false;
    bool createEntity = false;
};

class Scene
{
private:
    void processInput(GLFWwindow* window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    
    void CreateEntity()
    {
        Entity entity = Entity(m_sceneFlags.entityIsLight);
        m_entities.push_back(entity);
        
        m_sceneFlags.createEntity = false;
        m_sceneFlags.entityIsLight = false;
    }
public:
    Scene(Application application)
    {
        m_window = application.window;
    }
    ~Scene()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }
    void onUpdateRuntime()
    {
        RenderApi renderer = RenderApi();
        ContentBrowserPanel contentBrowserPanel = ContentBrowserPanel();
        
        while(!glfwWindowShouldClose(m_window)) {
            processInput(m_window);
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            if(m_sceneFlags.createEntity)
            {
                CreateEntity();
                if(m_entities.size() == 1)
                {
                    renderer.Create(m_entities[0].m_vertices);
                }
            }
            
            for(auto& entity : m_entities)
            {
                m_entityShader.Use();
                
                m_entityShader.Set1fUniform("hasLightComponent", entity.m_hasLightComponent);
                m_entityShader.Set1fUniform("useTexturing", 0);
                entity.SetMVPMatrix(m_entityShader);
               
                if(entity.m_orbitX)
                    entity.OrbitX();
                if(entity.m_orbitY)
                    entity.OrbitY();
                
                if(entity.textureID)
                    entity.SetTexture(m_entityShader);
                
                renderer.Draw();
            }
            
            for(int i = 0; i < m_entities.size(); i++)
            {
                m_entityShader.Use();

                auto& entity = m_entities[i];
                if(entity.m_hasLightComponent)
                {
                    char posBuffer[30];
                    sprintf(posBuffer, "dirLights[%d].position", i);
                    
                    char colorBuffer[30];
                    sprintf(colorBuffer, "dirLights[%d].color", i);
                    
                    m_entityShader.Set3fUniform(posBuffer, entity.m_transform);
                    m_entityShader.Set3fUniform(colorBuffer, entity.m_color);
                }
            }
            
            
            //UI
            ImGui::Begin("Sidebar");

            if(ImGui::BeginMenu("Create"))
            {
                if(ImGui::MenuItem("Entity"))
                {
                    m_sceneFlags.createEntity = true;
                }
                if(ImGui::MenuItem("Light"))
                {
                    m_sceneFlags.entityIsLight = true;
                    m_sceneFlags.createEntity = true;
                }
                ImGui::EndMenu();
            }

            if(m_entities.size() > 0)
            {
                for(auto& entity : m_entities)
                {
                    auto i = &entity - &m_entities[0];
                    bool isLight = entity.m_hasLightComponent;

                    ImGui::PushID((int)i);

                    if(isLight)
                    {
                        ImGui::Text("Light %i", (int)i);
                        ImGui::Checkbox("OrbitX", &entity.m_orbitX);
                        ImGui::Checkbox("OrbitY", &entity.m_orbitY);
                        ImGui::SliderFloat3("Transform", (float*)&entity.m_transform, -10.0f, 10.0f);
                        ImGui::ColorEdit3("Color", (float*)&entity.m_color);
                    } else {
                        ImGui::Text("Cube %i", (int)i);
                        ImGui::SliderFloat("Rotation Degrees", &entity.m_rotationDegrees, 0.0f, 360.0f);
                        ImGui::Text("Rotation Axis");
                        ImGui::Checkbox("X", &entity.m_rotateX);
                        ImGui::Checkbox("Y", &entity.m_rotateY);
                        ImGui::Checkbox("Z", &entity.m_rotateZ);
                        ImGui::SliderFloat3("Transform", (float*)&entity.m_transform, -10.0f, 10.0f);
                        ImGui::Text("Scale");
                        ImGui::InputFloat3("Scaling", (float*)&entity.m_scale);
                        ImGui::ColorEdit3("Color", (float*)&entity.m_color);
                        
                        ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
                        if(ImGui::BeginDragDropTarget())
                        {
                            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
                            {
                                const char* path = (const char*)payload->Data;
                                
                                Texture2D texture = Texture2D();
                                texture.Create(path, ".jpeg");
                                texture.Load();
                                
                                entity.textureID = texture.m_textureId;
                            }
                            ImGui::EndDragDropTarget();
                        }
                    }


                    ImGui::PopID();
                }
            }

            ImGui::End();

            contentBrowserPanel.OnImGuiRender();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(m_window);
        }
    }
private:
    GLFWwindow* m_window;
    std::vector<Entity> m_entities;
    SceneFlags m_sceneFlags;
    Shaders m_entityShader = Shaders("Shaders/Object/VertexShader.glsl", "Shaders/Object/FragmentShader.glsl");
};


