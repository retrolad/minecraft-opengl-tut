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
        std::vector<Chunk> m_chunks;
};

#endif
