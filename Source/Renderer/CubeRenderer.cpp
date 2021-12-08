#include "CubeRenderer.h"

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

void CubeRenderer::render()
{
    m_shader.use();
    m_texture.Bind(0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}