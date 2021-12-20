#ifndef CHUNKBLOCK_H
#define CHUNKBLOCK_H

#include "BlockId.h"

class BlockData;
class BlockType;

struct ChunkBlock
{
    ChunkBlock() = default;

    ChunkBlock(BlockId id);
    ChunkBlock(Block_t id);

    const BlockData& getData() const;
    const BlockType& getType() const;

    bool operator==(const ChunkBlock& other) const
    {
        return id == other.id;
    }

    Block_t id = 2;
};

#endif 