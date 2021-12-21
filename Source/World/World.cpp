#include "World.h"

World::World()
{
    for(int x = 0; x < 16; x++)
    {
        for(int z = 0; z < 16; z++)
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

    if(cX < 0 || cX >= 16) return BlockId::Void;
    if(cZ < 0 || cZ >= 16) return BlockId::Void;

    return m_chunks[cX * 16 + cZ].getBlock(bX, y, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    int bX = x % CHUNK_SIZE;
    int bZ = z % CHUNK_SIZE;

    if(cX < 0 || cX >= 16) return;
    if(cZ < 0 || cZ >= 16) return;

    m_chunks[cX * 16 + cZ].setBlock(bX, y, bZ, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
    setBlock(x, y, z, block);

    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    m_chunks[cX * 16 + cZ].makeMeshes();
}

void World::renderWorld(Renderer& renderer)
{
    for(auto& chunk : m_chunks)
        chunk.drawChunks(renderer);
}
