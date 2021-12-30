#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../../Renderer/Renderer.h"
#include "../../Maths/PerlinNoise.h"

#include <iostream>
#include <ctime>


int Chunk::nextID = 0;

Chunk::Chunk(const glm::ivec2& location, World& world)
: m_location(location)
{
    m_id = ++nextID;

    static PerlinNoise noise;

    std::array<int, CHUNK_SIZE * CHUNK_SIZE> heightMap;
    int maxHeight = 0;

    for(int z = 0; z < CHUNK_SIZE; z++)
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        int h = (int)(noise.getHeight(x, z, m_location.x, m_location.y) * 255);
        heightMap[x + z * CHUNK_SIZE] = h;

        if(h > maxHeight) maxHeight = h;
    }

    for(int y = 0; y < maxHeight / CHUNK_SIZE + 1; y++)
    {
        m_chunks.emplace_back(glm::ivec3(location.x, y, location.y), world);
    }

    for(int z = 0; z < 16; z++)
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < maxHeight + 1; y++)
        {
            int h = heightMap[x + z * CHUNK_SIZE];
            if(y < h - 8)
            {
                setBlock(x, y, z, BlockId::Stone); 
            }
            else if(y < h - 1)
            {
                setBlock(x, y, z, BlockId::Dirt);
            }
            else if(y == h - 1)
            {
                setBlock(x, y, z, BlockId::Grass);
            }
            else 
            {
                setBlock(x, y, z, BlockId::Void);
            }
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
    // std::cout << "[Chunk " << m_id << "] has been built\n";    
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
        // TODO add chunk section
    }
    return m_chunks.at(index);
}

bool Chunk::beenLoaded() const
{
    return m_isLoaded;
}