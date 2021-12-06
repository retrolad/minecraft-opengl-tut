#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>

struct Context
{
    Context();
    ~Context();

    GLFWwindow* window;
};

#endif