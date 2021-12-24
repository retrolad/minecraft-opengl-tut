#ifndef RENDERER_H
#define RENDERER_H

#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"
#include "TextRenderer.h"

#include <GLFW/glfw3.h>

class Renderer
{
    public:
        Renderer();

        void drawCube(const glm::vec3& pos);
        void drawChunk(const ChunkMesh& mesh);
        void drawText(const Text& text);

        void EndFrame(GLFWwindow* window, const Camera& camera);
        
    private:
        CubeRenderer m_cubeRenderer;
        ChunkRenderer m_chunkRenderer;
        SkyboxRenderer m_skyboxRenderer;
        TextRenderer m_textRenderer;
};

#endif