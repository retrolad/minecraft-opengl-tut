#ifndef BLOCKDATABASE_H
#define BLOCKDATABASE_H

#include "BlockId.h"
#include "BlockTypes/BlockType.h"
#include "../Utils/Singleton.h"

#include <array>
#include <memory>

class BlockDatabase : Singleton 
{
    public:
        static BlockDatabase& get();

        const BlockType& getBlock(BlockId id) const;
        const BlockData& getData (BlockId id)  const;

    private:
        BlockDatabase();

        std::array<std::unique_ptr<BlockType>, (size_t)BlockId::NTYPES> m_blocks; 
};

#endif 