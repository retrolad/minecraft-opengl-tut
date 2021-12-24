#include "ChunkManager.h"

ChunkManager::ChunkManager(World& world)
: m_world(&world)
{

}

Chunk& ChunkManager::getChunk(int x, int z)
{
    if(m_chunks.find({x,z}) == m_chunks.end())
    {
        // LocationXZ locKey {x,z};
        // Chunk      chunk  {{x,z}, *m_world};
        m_chunks.emplace(glm::ivec2{x,z}, Chunk{{x,z}, *m_world});
    }

    return m_chunks.at({x,z});
}

const std::unordered_map<glm::ivec2, Chunk>& ChunkManager::getChunks() const
{
    return m_chunks;
}
