#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/Renderer.h"

Chunk::Chunk()
{
    for(int i = 0; i < 8; i++)
    {
        m_chunks.emplace_back(glm::ivec3(i, 0, 0));
        auto& chunk = m_chunks.back();

        ChunkMeshBuilder builder(m_chunks.back());
        builder.buildMesh(m_chunks.back().m_mesh);
        m_chunks.back().m_mesh.createModel();
    }
}

void Chunk::drawChunks(Renderer& renderer)
{
    for(auto& chunk : m_chunks)
    {
        renderer.drawChunk(chunk.m_mesh);
    }
}