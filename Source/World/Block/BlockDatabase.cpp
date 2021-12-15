#include "BlockDatabase.h"

BlockDatabase::BlockDatabase()
{
    m_blocks[(int)BlockId::Grass] = std::make_unique<DefaultBlock>("Grass");
}

BlockDatabase& BlockDatabase::get()
{
    static BlockDatabase db;
    return db; 
}

const BlockType& BlockDatabase::getBlock(BlockId id) const 
{   
    return *m_blocks[(int)id];
}

const BlockData& BlockDatabase::getData(BlockId id) const
{
    return m_blocks[(int)id]->getData();
}