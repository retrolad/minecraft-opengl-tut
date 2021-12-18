#ifndef CHUNK_H
#define CHUNK_H

#include "ChunkSection.h"

class Renderer;

class Chunk
{
    public:
        Chunk();

        void drawChunks(Renderer& renderer);

    private:
        std::vector<ChunkSection> m_chunks;
};

#endif