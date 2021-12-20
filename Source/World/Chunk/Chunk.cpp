#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/Renderer.h"

Chunk::Chunk(const glm::ivec2& location, World& world)
: m_location(location)
{
    for(int y = 0; y < 3; y++)
    {
        m_chunks.emplace_back(glm::ivec3(location.x, y, location.y), world);
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

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
    if(outOfBound(x, y, z))
    {
        return;
    }
}

ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
    if(outOfBound(x, y, z))
    {
        return BlockId::Void;
    }

    // Block's y position in chunk section
    int bY = y % CHUNK_SIZE;

    m_chunks[y / CHUNK_SIZE].getBlock(x, bY, z);
}

bool Chunk::outOfBound(int x, int y, int z) const
{
    if(x >= CHUNK_SIZE) return true;
    if(z >= CHUNK_SIZE) return true;

    if(x < 0) return true;
    if(y < 0) return true;
    if(z < 0) return true;

    if(y >= m_chunks.size() * CHUNK_SIZE)
    {
        return true;
    }

    return 0;
}

void Chunk::drawChunks(Renderer& renderer)
{
    for(auto& chunk : m_chunks)
    {
        renderer.drawChunk(chunk.m_mesh);
    }
}