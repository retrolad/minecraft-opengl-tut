#include "Renderer.h"

void Renderer::EndFrame(GLFWwindow* window, const Camera& camera)
{
    glClearColor(0.1f, 0.1f, 0.1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cubeRenderer.render(camera);

    // Swap back and front buffers
    glfwSwapBuffers(window);
    // Process nad handle window and input events
    glfwPollEvents();
}