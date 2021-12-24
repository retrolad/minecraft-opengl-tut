#ifndef WORLD_H
#define WORLD_H

#include "Chunk/ChunkManager.h"

#include <queue>
#include <unordered_map>

class Renderer;

class World
{
    public:
        World();

        ChunkBlock getBlock (int x, int y, int z);
        void setBlock       (int x, int y, int z, ChunkBlock block);
        void editBlock      (int x, int y, int z, ChunkBlock block);

        void addChunk(int x, int z);

        void renderWorld(Renderer& renderer);
    private:
        ChunkManager m_chunkManager;
        // std::vector<Chunk> m_chunks;
        std::queue<glm::ivec3> m_chunksQueue;
        std::vector<glm::ivec3> m_modChunks;
};

#endif
