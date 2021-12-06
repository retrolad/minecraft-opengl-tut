#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

#include "Shaders/Shader.h"
#include "Texture/Texture.h"

class CubeRenderer
{
public:
    CubeRenderer();
    void render();

private:
    Shader m_shader;
    Texture m_texture;

    GLuint m_vao;
};

#endif