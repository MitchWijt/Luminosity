#pragma once

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

void instantiateGLFW();
int instantiateGLEW(GLFWwindow* window);
GLFWwindow* createWindow();

