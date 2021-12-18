#ifndef WORLD_H
#define WORLD_H

#include "Chunk/Chunk.h"

class Renderer;

class World
{
    public:
        World();

        void renderWorld(Renderer& renderer);
    private:
        Chunk m_chunk;
};

#endif
