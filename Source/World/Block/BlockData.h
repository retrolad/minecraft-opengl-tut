#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

#include "../../Utils/NonCopyable.h"
#include "../../Maths/TextureMath.h"
#include <string>

struct BlockDataStorage : public NonCopyable
{
    Texel topCoords;
    Texel sideCoords;
    Texel bottomCoords;
};

class BlockData : public NonCopyable
{
    public:
        BlockData(const std::string& fileName);

        const BlockDataStorage& getBlockData() const;

    private:
        BlockDataStorage m_data;
};

#endif