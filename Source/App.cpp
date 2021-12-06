#include "App.h"

#include <iostream>

void App::run()
{
    std::cout << glGetString(GL_VERSION) << std::endl;

    while(!glfwWindowShouldClose(m_context.window))
    {
        m_renderer.EndFrame(m_context.window);
    }
}