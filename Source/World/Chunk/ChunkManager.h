#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "Chunk.h"

#include <glm/gtx/hash.hpp>
#include <unordered_map>

// TODO create hash and use this struct
// as map key instead of glm::ivec2
struct LocationXZ
{
    int x,z;
};

class ChunkManager
{
    public:
        ChunkManager(World& world);

        Chunk& getChunk(int x, int z);
        const std::unordered_map<glm::ivec2, Chunk>& getChunks() const;

    private:
        std::unordered_map<glm::ivec2, Chunk> m_chunks; 
        World* m_world;
};

#endif // CHUNKMANAGER_H
