#include "TextShader.h"

TextShader::TextShader(const std::string& vertexPath, 
                       const std::string& fragmentPath)
: Shader(vertexPath, fragmentPath)
{
    getUniforms();
}

void TextShader::setProjectionMatrix()
{
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    setMatrix4(m_locationProjectionMatrix, projection);
}

void TextShader::setTextColor(const glm::vec3& color)
{
    setVector3f(m_locationTextColor, color.x, color.y, color.z);
}

void TextShader::getUniforms()
{
    m_locationProjectionMatrix  = glGetUniformLocation(m_id, "projection");
    m_locationTextColor         = glGetUniformLocation(m_id, "textColor");
}