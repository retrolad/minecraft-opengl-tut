#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"

#include "../Block/BlockDatabase.h"

#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

namespace
{
    const std::vector<GLfloat> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };

    const std::vector<GLfloat> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1 ,0,
    };
    const std::vector<GLfloat> bottomFace
    {
        0, 0, 0, 
        1, 0, 0,
        1, 0, 1,
        0, 0, 1,
    };
    const std::vector<GLfloat> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
    };
    const std::vector<GLfloat> leftFace
    {
        0, 0, 0, 
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
    };

    const std::vector<GLfloat> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1
    };

}

int ChunkMeshBuilder::meshId = 1;

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk)
: m_pChunk(&chunk)
{

}

void ChunkMeshBuilder::buildMesh(ChunkMesh& mesh)
{
    auto start = glfwGetTime();
    m_pMesh = &mesh;

    for(int y = 0; y < CHUNK_SIZE; y++)
    for(int x = 0; x < CHUNK_SIZE; x++)
    for(int z = 0; z < CHUNK_SIZE; z++)
    {
        // ChunkBlock at pos (x,y,z) of this chunk section
        auto block = m_pChunk->getBlock(x, y, z);
        if(block == BlockId::Void) continue;

        // ChunkBlock uses BlockDatabase to retrieve the actual block
        // by chunk block's id
        // getData()                  -> BlockData&
        // BlockData().getBlockData() -> BlockDataStorage&
        auto data = &block.getData().getBlockData();

        // Try to add each face of the block to the mesh
        // Do not draw bottom chunks faces
        // if(y == 0 && m_pChunk->getLocation().y == 0)
            tryAddFace(bottomFace, data->bottomCoords, {x, y, z}, {x,   y-1, z});
        tryAddFace(topFace,    data->topCoords,    {x, y, z}, {x,   y+1, z});
        tryAddFace(frontFace,  data->sideCoords,   {x, y, z}, {x,   y,   z+1});
        tryAddFace(backFace,   data->sideCoords,   {x, y, z}, {x,   y,   z-1});
        tryAddFace(leftFace,   data->sideCoords,   {x, y, z}, {x-1, y,   z});
        tryAddFace(rightFace,  data->sideCoords,   {x, y, z}, {x+1, y,   z});
    }

    auto end = glfwGetTime();
    // std::cout << "[Mesh " << meshId++ << "] built in: " << (end - start) * 1000 << "ms\n";    
}

void ChunkMeshBuilder::tryAddFace(const std::vector<GLfloat>& blockFace,
                                  const glm::ivec2& textureCoords,
                                  const glm::ivec3& blockPosition,
                                  const glm::ivec3& facing)
{   
    if(m_pChunk->getBlock(facing.x, facing.y, facing.z) == BlockId::Void)
    {
        auto texCoords = BlockDatabase::get().m_textureAtlas.getTexture(textureCoords);
        m_pMesh->addFace(blockFace, texCoords, m_pChunk->getLocation(), blockPosition);
    }
}