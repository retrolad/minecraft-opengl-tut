#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "../../Maths/glm.h"
#include "ChunkMesh.h"

#include <array>

class World;

class ChunkSection
{
    public:
        ChunkSection(glm::ivec3 location, World& world);
        // ChunkSection(glm::ivec3 pos);

        void setBlock       (int x, int y, int z, ChunkBlock block);
        ChunkBlock getBlock (int x, int y, int z) const;

        const glm::ivec3 getLocation() const;

        void buildMesh();

        ChunkMesh m_mesh;
    private:
        static bool outOfBounds (int value);
        static int  getIndex    (int x, int y, int z);

        glm::ivec3 toWorldPosition(int x, int y, int z) const;

        std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;

        glm::ivec3 m_location;

        World* m_pWorld;
};

#endif 