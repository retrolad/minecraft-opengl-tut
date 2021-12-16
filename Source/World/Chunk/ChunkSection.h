#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"

#include <array>

class ChunkSection
{
    public:
        ChunkSection();

        void setBlock       (int x, int y, int z, ChunkBlock block);
        ChunkBlock getBlock (int x, int y, int z) const;
    private:
        static bool outOfBounds (int value);
        static int  getIndex    (int x, int y, int z);

        std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
};

#endif 