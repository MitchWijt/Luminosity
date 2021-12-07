#pragma once
#include "lheaders.hpp"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"


class Application
{
private:
    void instantiateGLFW()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    int instantiateGLEW(GLFWwindow* window)
    {
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        
        if(glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
        }
        
        return 1;
    }

    void instantiateImGUI(GLFWwindow* window)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();
    }
public:
    Application(const std::string& name)
    {
        instantiateGLFW();
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        instantiateGLEW(window);
        instantiateImGUI(window);
        
        glEnable(GL_DEPTH_TEST);
        
        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        
        if(window == NULL)
        {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
        }
        
        glViewport(0, 0, screenWidth, screenHeight);        
    }
    
public:
    unsigned int width = 1200;
    unsigned int height = 900;
    GLFWwindow* window;
    bool running = true;
    static Application* s_Instance;

};
