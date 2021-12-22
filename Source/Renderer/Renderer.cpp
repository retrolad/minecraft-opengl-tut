#include "Renderer.h"

void Renderer::drawCube(const glm::vec3& pos)
{
    // m_cubeRenderer.add(pos);
}

void Renderer::drawChunk(const ChunkMesh& mesh)
{
    m_chunkRenderer.add(mesh);
}

void Renderer::EndFrame(GLFWwindow* window, const Camera& camera)
{
    glClearColor(0.2f, 0.45f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // Enable depth buffer (Z buffer)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // Cull back faces
    glCullFace(GL_BACK);

    // m_cubeRenderer.render(camera);
    m_chunkRenderer.render(camera);
    m_skyboxRenderer.render(camera);

    // Swap back and front buffers
    glfwSwapBuffers(window);
    // Process nad handle window and input events
    glfwPollEvents();
}