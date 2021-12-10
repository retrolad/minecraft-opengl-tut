#ifndef RENDERER_H
#define RENDERER_H

#include "CubeRenderer.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
    void EndFrame(GLFWwindow* window, const Camera& camera);
private:
    CubeRenderer cubeRenderer;
};

#endif