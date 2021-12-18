#include "World.h"

World::World()
{

}

void World::renderWorld(Renderer& renderer)
{
    m_chunk.drawChunks(renderer);
}
