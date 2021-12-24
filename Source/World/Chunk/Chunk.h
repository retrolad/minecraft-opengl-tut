#ifndef CHUNK_H
#define CHUNK_H

#include "ChunkSection.h"

class Renderer;

class Chunk
{
    public:
        Chunk(const glm::ivec2& location, World& world);

        void makeMeshes();

        ChunkBlock getBlock(int x, int y, int z) const;
        void setBlock(int x, int y, int z, ChunkBlock block);  

        void drawChunks(Renderer& renderer) const;

        ChunkSection& getSection(int index);

        bool beenLoaded() const;

    private:
        bool outOfBound(int x, int y, int z) const;

        std::vector<ChunkSection>   m_chunks;
        glm::ivec2                  m_location;
        
        bool m_isLoaded = false;

        int m_id; 
        
        static int nextID;
};

#endif