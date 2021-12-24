#include "Renderer.h"

Renderer::Renderer()
{
    m_textRenderer.load("NeoSans", 16);
}

void Renderer::drawCube(const glm::vec3& pos)
{
    // m_cubeRenderer.add(pos);
}

void Renderer::drawChunk(const ChunkMesh& mesh)
{
    m_chunkRenderer.add(mesh);
}

void Renderer::drawText(const Text& text)
{
    m_textRenderer.addText(text);
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // m_cubeRenderer.render(camera);
    m_chunkRenderer.render(camera);
    m_skyboxRenderer.render(camera);
    m_textRenderer.render();

    // Swap back and front buffers
    glfwSwapBuffers(window);
    // Process nad handle window and input events
    glfwPollEvents();
}