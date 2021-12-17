#include "ChunkMesh.h"

#include "../WorldConstants.h"

ChunkMesh::ChunkMesh()
{
    
}

/** 
 * @param blockFace     vertex positions of the face
 * @param textureCoords texture coordinates on the texture image
 * @param chunkPosition location of the chunk in the world
 * @param blockPosition block position in the chunk 
*/
void ChunkMesh::addFace(const std::vector<GLfloat>& blockFace,
             const std::vector<GLfloat>& textureCoords,
             const glm::ivec3&           chunkPositions,
             const glm::ivec3&           blockPosition)
{
    auto& vertices = m_mesh.vertexPositions; 
    auto& textures = m_mesh.textureCoords;
    auto& indices  = m_mesh.indices;

    // There are 4 vertices on each face
    for(int vertexCount = 0, index = 0; vertexCount < 4; vertexCount++)
    {
        // Chunk size is 16, so chunk position is proportional to chunk size 0,16,32...
        vertices.push_back(blockFace[index++] + chunkPositions.x * CHUNK_SIZE + blockPosition.x);
        vertices.push_back(blockFace[index++] + chunkPositions.y * CHUNK_SIZE + blockPosition.y);
        vertices.push_back(blockFace[index++] + chunkPositions.z * CHUNK_SIZE + blockPosition.z);
    }

    textures.insert(textures.end(), textureCoords.begin(), textureCoords.end());

    indices.insert(indices.end(), {
        m_indiceIdx,
        m_indiceIdx + 1,
        m_indiceIdx + 2,

        m_indiceIdx + 2,
        m_indiceIdx + 3,
        m_indiceIdx,
    });

    m_indiceIdx += 4;
    m_verticesCount += 4;
}

void ChunkMesh::createModel()
{
    m_model.construct(m_mesh);
}

const Model& ChunkMesh::getModel() const 
{
    return m_model;
}

int ChunkMesh::getVerticesCount() const
{
    return m_verticesCount;
}
