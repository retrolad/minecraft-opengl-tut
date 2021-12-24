#include "SkyboxRenderer.h"

#include "../Camera.h"

SkyboxRenderer::SkyboxRenderer()
: m_cubeTexture({
    "right.png",
    "left.png",
    "top.png",
    "bottom.png",
    "back.png",
    "front.png"
})
{
    constexpr GLfloat SIZE = 500.0f;
    std::vector<GLfloat> skyboxVertices = {
        //Right
        SIZE, -SIZE,  SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE,  SIZE, -SIZE,
        SIZE,  SIZE,  SIZE,
        //Left
        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE, -SIZE,
        //Top
        -SIZE, SIZE,  SIZE,
         SIZE, SIZE,  SIZE,
         SIZE, SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,
        //Bottom
        -SIZE, -SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE,  SIZE,
        //Back
         SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,

        //Front
        -SIZE, -SIZE, SIZE,
         SIZE, -SIZE, SIZE,
         SIZE,  SIZE, SIZE,
        -SIZE,  SIZE, SIZE,
    };

    std::vector<GLuint> indices
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    m_model.construct({skyboxVertices, {}, indices});
}

void SkyboxRenderer::render(const Camera& camera)
{
    glDisable(GL_CULL_FACE);
    m_shader.use();
    m_model.bindVAO();
    m_cubeTexture.bindTexture();

    m_shader.setProjectionMatrix (camera.getProjectionMatrix());
    m_shader.setViewMatrix       (camera.getViewMatrix());

    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}