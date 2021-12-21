#include "World.h"

constexpr int worldSize = 16;

World::World()
{
    for(int x = 0; x < worldSize; x++)
    {
        for(int z = 0; z < worldSize; z++)
        {
            m_chunks.emplace_back(glm::ivec2(x, z), *this);
        }
    }

    for(auto& chunk : m_chunks)
        chunk.makeMeshes();
}

ChunkBlock World::getBlock(int x, int y, int z) const
{
    // Find out which chunk this block is located at
    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    // Find block's position in that chunk
    int bX = x % CHUNK_SIZE;
    int bZ = z % CHUNK_SIZE;

    if(cX < 0 || cX >= worldSize) return BlockId::Void;
    if(cZ < 0 || cZ >= worldSize) return BlockId::Void;

    return m_chunks[cX * worldSize + cZ].getBlock(bX, y, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    int bX = x % CHUNK_SIZE;
    int bZ = z % CHUNK_SIZE;

    if(cX < 0 || cX >= worldSize) return;
    if(cZ < 0 || cZ >= worldSize) return;

    m_chunks[cX * worldSize + cZ].setBlock(bX, y, bZ, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    setBlock(x, y, z, block);
    m_modChunks.push_back(&m_chunks[cX * worldSize + cZ]);

    // Rerender neighbour mesh if editing edge block
    // int bX = x % CHUNK_SIZE;
    // int bZ = z % CHUNK_SIZE;

    // if(bX == 0) m_chunks[(cX - 1) * worldSize + cZ].makeMeshes();
    // if(bZ == 0) m_chunks[cX * worldSize + (cZ - 1)].makeMeshes();
    // if(bX == CHUNK_SIZE - 1) m_chunks[(cX + 1) * worldSize + cZ].makeMeshes();
    // if(bZ == CHUNK_SIZE - 1) m_chunks[cX * worldSize + (cZ + 1)].makeMeshes();
}

void World::renderWorld(Renderer& renderer)
{
    for(auto& chunk : m_modChunks)
        chunk->makeMeshes();

    m_modChunks.clear();

    for(auto& chunk : m_chunks)
        chunk.drawChunks(renderer);
}
