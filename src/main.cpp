#include <iostream>
#include "Scene/Scene.hpp"

int main() {
    GLFWwindow* window = createWindow();
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return -1;
}
