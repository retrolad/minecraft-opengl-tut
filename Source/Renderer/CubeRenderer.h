#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

#include "Shaders/Shader.h"
#include "Texture/Texture.h"
#include "../Model.h"
#include "../Camera.h"
#include "../Texture/TextureAtlas.h"
#include "../World/Block/BlockTypes/BlockType.h"

class CubeRenderer
{
public:
    CubeRenderer();
    void render(const Camera& camera);

private:
    Shader m_shader;
    Model m_model;

    GLuint m_vao;

    TextureAtlas m_textureAtlas;
};

#endif