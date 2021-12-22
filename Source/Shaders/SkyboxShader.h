#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Shader.h"

class SkyboxShader : public Shader
{
    public:
        SkyboxShader(const std::string& vertexPath = "SkyboxVertex",
                    const std::string& fragmentPath = "SkyboxFragment");

        void setProjectionMatrix(const glm::mat4& projMatrix);
        void setViewMatrix      (glm::mat4 viewMatrix);

        void getUniforms() override;

    private:
        GLint m_locationProjectionMatrix;
        GLint m_locationViewMatrix;
};

#endif // SKYBOXSHADER_H
