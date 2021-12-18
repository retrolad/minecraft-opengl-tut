#include "World.h"

World::World()
{
    for(int x = 0; x < 16; x++)
    {
        for(int z = 0; z < 16; z++)
        {
            m_chunks.emplace_back(glm::ivec2(x, z));
        }
    }

    for(auto& chunk : m_chunks)
        chunk.makeMeshes();
}

void World::renderWorld(Renderer& renderer)
{
    for(auto& chunk : m_chunks)
        chunk.drawChunks(renderer);
}
