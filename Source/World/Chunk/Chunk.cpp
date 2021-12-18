#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/Renderer.h"

Chunk::Chunk(const glm::ivec2& location)
: m_location(location)
{
    for(int y = 0; y < 3; y++)
    {
        m_chunks.emplace_back(glm::ivec3(location.x, y, location.y));
    }
}

void Chunk::makeMeshes()
{
    for(auto& chunk : m_chunks)
    {
        ChunkMeshBuilder builder(chunk);
        builder.buildMesh(chunk.m_mesh);
        chunk.m_mesh.createModel();
    }
}

void Chunk::drawChunks(Renderer& renderer)
{
    for(auto& chunk : m_chunks)
    {
        renderer.drawChunk(chunk.m_mesh);
    }
}