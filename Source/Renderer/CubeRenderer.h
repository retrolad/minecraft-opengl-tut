#ifndef CUBERENDERER_H
#define CUBERENDERER_H

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

    void add(const glm::vec3& pos);
    
private:
    Shader m_shader;
    Model m_model;
    TextureAtlas m_textureAtlas;

    std::vector<glm::vec3> m_cubes;
};

#endif