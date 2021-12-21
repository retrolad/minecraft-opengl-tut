#ifndef WORLD_H
#define WORLD_H

#include "Chunk/Chunk.h"

class Renderer;

class World
{
    public:
        World();

        ChunkBlock getBlock (int x, int y, int z) const;
        void setBlock       (int x, int y, int z, ChunkBlock block);
        void editBlock      (int x, int y, int z, ChunkBlock block);

        void renderWorld(Renderer& renderer);
    private:
        std::vector<Chunk> m_chunks;
        std::vector<Chunk*> m_modChunks;
};

#endif
