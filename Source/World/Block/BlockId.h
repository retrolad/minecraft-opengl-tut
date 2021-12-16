#ifndef BLOCKID_H
#define BLOCKID_H

#include <cstdint>

typedef uint8_t Block_t;

enum class BlockId : Block_t 
{
    Grass = 0,
    Dirt,

    NTYPES
};

#endif