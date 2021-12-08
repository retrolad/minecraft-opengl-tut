#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

#include "Shaders/Shader.h"
#include "Texture/Texture.h"
#include "../Model.h"

class CubeRenderer
{
public:
    CubeRenderer();
    void render();

private:
    Shader m_shader;
    Texture m_texture;
    Model m_model;

    GLuint m_vao;
};

#endif