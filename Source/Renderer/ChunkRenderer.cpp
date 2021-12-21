#include "ChunkRenderer.h"

#include "../World/Block/BlockDatabase.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../Camera.h"

#include <iostream>

ChunkRenderer::ChunkRenderer()
{

}

void ChunkRenderer::add(const ChunkMesh& mesh)
{
    m_chunks.push_back(&mesh);
}

void ChunkRenderer::render(const Camera& camera)
{
    m_shader.use();
    BlockDatabase::get().m_textureAtlas.Bind();

    m_shader.setModelMatrix(glm::mat4(1.0f));
    m_shader.setProjectionViewMatrix(camera.getProjectionMatrix() * 
                                     camera.getViewMatrix());

    for(const ChunkMesh* mesh : m_chunks)
    {
        const ChunkMesh& m = *mesh;

        m.getModel().bindVAO();
        glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    m_chunks.clear();
}