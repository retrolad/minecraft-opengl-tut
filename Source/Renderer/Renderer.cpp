#include "Renderer.h"

void Renderer::drawCube(const glm::vec3& pos)
{
    m_cubeRenderer.add(pos);
}

void Renderer::EndFrame(GLFWwindow* window, const Camera& camera)
{
    glClearColor(0.2f, 0.45f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_cubeRenderer.render(camera);

    // Swap back and front buffers
    glfwSwapBuffers(window);
    // Process nad handle window and input events
    glfwPollEvents();
}