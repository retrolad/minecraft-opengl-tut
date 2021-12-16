#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "Shaders/Shader.h"

class Camera;
class ChunkMesh;

class ChunkRenderer
{
    public:
        ChunkRenderer();

        void render(const Camera& camera);
        void add(const ChunkMesh& mesh);

    private:
        std::vector<const ChunkMesh*> m_chunks;
        Shader m_shader;
};

#endif 