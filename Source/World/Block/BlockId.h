#ifndef BLOCKID_H
#define BLOCKID_H

#include <cstdint>

typedef uint8_t Block_t;

enum class BlockId : Block_t 
{
    Void = 0,
    Grass,
    Dirt,

    NTYPES
};

#endif