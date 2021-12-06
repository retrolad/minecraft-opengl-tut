#ifndef RENDERER_H
#define RENDERER_H

#include "CubeRenderer.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
    void EndFrame(GLFWwindow* window);
private:
    CubeRenderer cubeRenderer;
};

#endif