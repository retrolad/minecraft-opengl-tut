#include "App.h"

#include <iostream>


void App::run()
{
    std::cout << glGetString(GL_VERSION) << std::endl;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(m_context.window))
    {
        float currentFrame = glfwGetTime();
        static float lastFrame = 0;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleEvents(deltaTime);
        m_camera.update();
        m_renderer.EndFrame(m_context.window, m_camera);
    }
}

void App::handleEvents(float deltaTime)
{
    // Handle independently of how fast CPU works
    if(isKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(m_context.window, true);
    }
    if(isKeyPressed(GLFW_KEY_W))
    {
        m_camera.processInput(FORWARD, deltaTime);
    }
    if(isKeyPressed(GLFW_KEY_S))
    {
        m_camera.processInput(BACKWARD, deltaTime);
    }
    if(isKeyPressed(GLFW_KEY_D))
    {
        m_camera.processInput(RIGHT, deltaTime);
    }
    if(isKeyPressed(GLFW_KEY_A))
    {
        m_camera.processInput(LEFT, deltaTime);
    }
}

bool App::isKeyPressed(int keyCode)
{
    return glfwGetKey(m_context.window, keyCode) == GLFW_PRESS;
}

