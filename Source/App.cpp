#include "App.h"

#include <iostream>

#include "World/Chunk/ChunkMeshBuilder.h"

App::App()
: m_player(&m_world)
{
    m_camera.bindEntity(m_player);
}

void App::run()
{
    std::cout << glfwGetTime() << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(m_context.window))
    {
        float currentFrame = glfwGetTime();
        static float lastFrame = 0;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        m_player.handleInput(m_context.window);
        m_player.update(deltaTime);
        m_camera.update();  
        m_fpsCounter.render(m_renderer);
        m_world.renderWorld(m_renderer);
        m_renderer.EndFrame(m_context.window, m_camera);
        
        handleEvents(deltaTime);
    }
}

void App::handleEvents(float deltaTime)
{
    // Handle independently of how fast CPU works
    if(isKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(m_context.window, true);
    }
}

bool App::isKeyPressed(int keyCode)
{
    return glfwGetKey(m_context.window, keyCode) == GLFW_PRESS;
}

