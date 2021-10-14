#include <iostream>
#include "Scene.hpp"

const GLint WIDTH = 800, HEIGHT = 600;

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

GLFWwindow* createWindow()
{
    instantiateGLFW();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Luminosity", nullptr, nullptr);
    instantiateGLEW(window);
    glEnable(GL_DEPTH_TEST);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        
        return (GLFWwindow*)-1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    return window;
}

