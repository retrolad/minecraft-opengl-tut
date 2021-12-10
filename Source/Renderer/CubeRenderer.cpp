#include "CubeRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/glfw3.h>

CubeRenderer::CubeRenderer()
{
    m_texture.loadFromFile("../Resources/Textures/brick.jpg");

    m_model.construct(
        {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        },
        {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        },
        {
            0, 1, 2,
            0, 2, 3
        }
    );

}

void CubeRenderer::render(const Camera& camera)
{
    m_shader.use();
    m_texture.Bind(0);
    // TODO bind vao

    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f + 3*sin(glfwGetTime())));
    // glUniformMatrix4fv(glGetUniformLocation(m_shader.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    m_shader.setProjectionViewMatrix(camera.getProjectionMatrix() * camera.getViewMatrix());
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}