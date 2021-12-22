#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../Model.h"
#include "../Texture/CubeTexture.h"
#include "../Shaders/SkyboxShader.h"

class Camera;

class SkyboxRenderer
{
    public:
        SkyboxRenderer();

        void render(const Camera& camera);
    
    private:
        Model m_model;
        CubeTexture m_cubeTexture;
        SkyboxShader m_shader;
};

#endif // SKYBOXRENDERER_H
