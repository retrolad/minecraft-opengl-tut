#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/Renderer.h"

#include <iostream>

int Chunk::nextID = 0;

Chunk::Chunk(const glm::ivec2& location, World& world)
: m_location(location)
{
    m_id = ++nextID;

    for(int y = 0; y < 3; y++)
    {
        m_chunks.emplace_back(glm::ivec3(location.x, y, location.y), world);
    }

    for(int y = 0; y < m_chunks.size() * CHUNK_SIZE; y++)
    for(int x = 0; x < 16; x++)
    for(int z = 0; z < 16; z++)
    {
        if(y < m_chunks.size() * CHUNK_SIZE - 8)
        {
            setBlock(x, y, z, BlockId::Stone); 
        }
        else if(y < m_chunks.size() * CHUNK_SIZE - 1)
        {
            setBlock(x, y, z, BlockId::Dirt);
        }
        else 
        {
            setBlock(x, y, z, BlockId::Grass);
        }
    }
}

void Chunk::makeMeshes()
{
    for(auto& chunk : m_chunks)
    {
        chunk.buildMesh();
    }

    m_isLoaded = true;
    std::cout << "[Chunk " << m_id << "] has been built\n";    
}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
    if(outOfBound(x, y, z))
    {
        return;
    }

    int bY = y % CHUNK_SIZE;
    m_chunks[y / CHUNK_SIZE].setBlock(x, bY, z, block);
}

ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
    if(outOfBound(x, y, z))
    {
        return BlockId::Void;
    }

    // Block's y position in chunk section
    int bY = y % CHUNK_SIZE;

    return m_chunks[y / CHUNK_SIZE].getBlock(x, bY, z);
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

void Chunk::drawChunks(Renderer& renderer) const
{
    for(auto& chunk : m_chunks)
    {
        renderer.drawChunk(chunk.m_mesh);
    }
}

ChunkSection& Chunk::getSection(int index)
{
    if(index >= m_chunks.size())
    {
        
    }
    return m_chunks.at(index);
}

bool Chunk::beenLoaded() const
{
    return m_isLoaded;
}