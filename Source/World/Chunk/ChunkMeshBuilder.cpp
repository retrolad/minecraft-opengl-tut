#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"

#include "../Block/BlockDatabase.h"

#include <vector>

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

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk)
: m_pChunk(&chunk)
{

}

void ChunkMeshBuilder::buildMesh(ChunkMesh& mesh)
{
    m_pMesh = &mesh;

    for(int y = 0; y < CHUNK_SIZE; y++)
    for(int x = 0; x < CHUNK_SIZE; x++)
    for(int z = 0; z < CHUNK_SIZE; z++)
    {
        auto block = m_pChunk->getBlock(x, y, z);
        if(block == 0) continue;

        auto data = &block.getData().getBlockData();

        auto textureCoords = BlockDatabase::get().m_textureAtlas.getTexture(data->topCoords);
        
        tryAddFace(frontFace,  data->sideCoords, {x, y, z});
        tryAddFace(backFace,   data->sideCoords, {x, y, z});
        tryAddFace(topFace,    data->topCoords,  {x, y, z});
        tryAddFace(bottomFace, data->sideCoords, {x, y, z});
        tryAddFace(leftFace,   data->sideCoords, {x, y, z});
        tryAddFace(rightFace,  data->sideCoords, {x, y, z});
    }    
}

void ChunkMeshBuilder::tryAddFace(const std::vector<GLfloat>& blockFace,
                                  const glm::ivec2& textureCoords,
                                  const glm::ivec3& blockPosition)
{   
    auto texCoords = BlockDatabase::get().m_textureAtlas.getTexture(textureCoords);
    m_pMesh->addFace(blockFace, texCoords, {0,0,0}, blockPosition);
}