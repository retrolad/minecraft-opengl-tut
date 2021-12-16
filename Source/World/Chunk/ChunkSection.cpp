#include "ChunkSection.h"

ChunkSection::ChunkSection()
: m_location({0,0,0})
{

}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock chunk)
{
    if(outOfBounds(x)) return;
    if(outOfBounds(y)) return;
    if(outOfBounds(z)) return;

    m_blocks[getIndex(x, y, z)] = chunk;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const 
{
    if(outOfBounds(x)) return BlockId::Void;
    if(outOfBounds(y)) return BlockId::Void;
    if(outOfBounds(z)) return BlockId::Void;

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

const glm::ivec3 ChunkSection::getLocation() const
{
    return m_location;
}