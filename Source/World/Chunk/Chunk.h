#ifndef CHUNK_H
#define CHUNK_H

#include "ChunkSection.h"

class Renderer;

class Chunk
{
    public:
        Chunk(const glm::ivec2& location);

        void makeMeshes();

        void drawChunks(Renderer& renderer);

    private:
        std::vector<ChunkSection>   m_chunks;
        glm::ivec2                  m_location;
};

#endif