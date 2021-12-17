#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include <vector>
#include <glad/glad.h> 

#include "../../Maths/glm.h"

class ChunkSection;
class ChunkMesh;

class ChunkMeshBuilder 
{
    public:
        ChunkMeshBuilder(ChunkSection& chunk);

        void buildMesh(ChunkMesh& mesh);
        void tryAddFace(const std::vector<GLfloat>& blockFace,
                        const glm::ivec2& textureCoords,
                        const glm::ivec3& blockPosition,
                        const glm::ivec3& facing);

        private:
            ChunkSection* m_pChunk;
            ChunkMesh*    m_pMesh;

            static int meshId;
};

#endif 