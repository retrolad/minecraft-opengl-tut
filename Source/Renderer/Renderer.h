#ifndef RENDERER_H
#define RENDERER_H

#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
    void drawCube(const glm::vec3& pos);
    void drawChunk(const ChunkMesh& mesh);
    void EndFrame(GLFWwindow* window, const Camera& camera);
private:
    // CubeRenderer m_cubeRenderer;
    ChunkRenderer m_chunkRenderer;
};

#endif