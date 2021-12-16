#include "ChunkSection.h"

ChunkSection::ChunkSection()
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
    if(outOfBounds(x)) return;
    if(outOfBounds(y)) return;
    if(outOfBounds(z)) return;

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