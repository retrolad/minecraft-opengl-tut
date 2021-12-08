#include "CubeRenderer.h"

CubeRenderer::CubeRenderer()
{
    m_model.construct(
        {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        },
        {},
        {
            0, 1, 2,
            0, 2, 3
        }
    );
}

void CubeRenderer::render()
{
    m_shader.use();
    // m_texture.Bind();

    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}