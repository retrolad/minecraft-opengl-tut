#ifndef BLOCKID_H
#define BLOCKID_H

#include <cstdint>

typedef uint8_t Block_t;

enum class BlockId : Block_t 
{
    Void    = 0,
    Grass   = 1,
    Dirt    = 2, 
    Stone   = 3,
    OakBark = 4,
    OakLeaf = 5,

    NTYPES
};

#endif