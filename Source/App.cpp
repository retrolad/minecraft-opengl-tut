#include "App.h"

#include <iostream>

#include "World/Chunk/ChunkMeshBuilder.h"

App::App()
{
    m_camera.bindEntity(m_player);

    ChunkMeshBuilder builder(m_chunk);
    builder.buildMesh(m_chunk.m_mesh);

    m_chunk.m_mesh.createModel();
}

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

        m_player.handleInput(m_context.window);
        m_player.update(deltaTime);
        m_camera.update();  

        m_renderer.drawChunk(m_chunk.m_mesh);

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

