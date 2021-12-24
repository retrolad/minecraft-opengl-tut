#ifndef TEXTSHADER_H
#define TEXTSHADER_H

#include "Shader.h"

class TextShader : public Shader 
{
    public:
        TextShader(const std::string& vertexPath = "TextVertex", 
                   const std::string& fragmentPath = "TextFragment");

        void setProjectionMatrix();
        void setTextColor(const glm::vec3& color);
    
    private:
        void getUniforms() override;

        GLint m_locationProjectionMatrix;
        GLint m_locationTextColor;
};

#endif // TEXTSHADER_H
