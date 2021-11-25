#pragma once
#include <vector>
#include "../Entity/Entity.hpp"
#include "../lheaders.hpp"

void instantiateGLFW();
int instantiateGLEW(GLFWwindow* window);
GLFWwindow* createWindow();

class Scene
{
public:
    static std::vector<Entity> m_registry;
};


