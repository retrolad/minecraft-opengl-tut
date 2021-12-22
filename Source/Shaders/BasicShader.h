#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"

class BasicShader : public Shader
{
    public:
        BasicShader(const std::string& vertexPath = "VertexShader", const std::string& fragmentPath = "FragmentShader");

        void setProjectionViewMatrix(const glm::mat4& projMatrix);
        void setViewMatrix(const glm::mat4& viewMatrix);
        void setModelMatrix(const glm::mat4& modelMatrix);
    
    protected:
        virtual void getUniforms() override;
    
    private:
        GLint m_locationProjectionViewMatrix;
        GLint m_locationModelMatrix;
};

#endif // BASICSHADER_H
