#include "ChunkSection.h"

#include "../World.h"
#include <iostream>

ChunkSection::ChunkSection(glm::ivec3 location, World& world)
: m_location(location),
  m_pWorld   (&world)
{

}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
    if(outOfBounds(x) ||
       outOfBounds(y) ||
       outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        m_pWorld->setBlock(location.x, location.y, location.z, block);
    }

    m_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const 
{
    if(outOfBounds(x) ||
       outOfBounds(y) ||
       outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        return m_pWorld->getBlock(location.x, location.y, location.z);
    } 

    return m_blocks[getIndex(x, y, z)];
}

bool ChunkSection::outOfBounds(int value)
{
    return value >= CHUNK_SIZE || value < 0;
}

int ChunkSection::getIndex(int x, int y, int z)
{
    return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

glm::ivec3 ChunkSection::toWorldPosition(int x, int y, int z) const
{
    return 
    {
        m_location.x * CHUNK_SIZE + x,
        m_location.y * CHUNK_SIZE + y,
        m_location.z * CHUNK_SIZE + z
    };
}

const glm::ivec3 ChunkSection::getLocation() const
{
    return m_location;
}

void ChunkSection::setLocation(int x, int y, int z)
{
    m_location = {x, y, z};
}
