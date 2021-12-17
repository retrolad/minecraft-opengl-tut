#include "App.h"

#include <iostream>

#include "World/Chunk/ChunkMeshBuilder.h"

App::App()
{
    m_camera.bindEntity(m_player);

    GLuint verN = 0;
    for(int x = 0; x < 4; x++)
    for(int z = 0; z < 4; z++)
    {
        auto& chunk = m_chunks[x*4+z];
        chunk.setLocation(x, 0, z);
        ChunkMeshBuilder builder(chunk);
        builder.buildMesh(chunk.m_mesh);
        
        chunk.m_mesh.createModel();

        verN += chunk.m_mesh.getVerticesCount(); 
    }

    std::cout << "Vertices count: [" << verN << "]" << std::endl; 
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

        for(int i = 0; i < m_chunks.size(); i++)
        {
            m_renderer.drawChunk(m_chunks[i].m_mesh);
        }

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

