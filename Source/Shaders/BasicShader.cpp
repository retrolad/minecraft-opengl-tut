#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexPath, const std::string& fragmentPath)
: Shader(vertexPath, fragmentPath)
{
    getUniforms();
}

void BasicShader::setProjectionViewMatrix(const glm::mat4& projMatrix)
{
    glUniformMatrix4fv(m_locationProjectionViewMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
}

void BasicShader::setModelMatrix(const glm::mat4& modelMatrix)
{
    glUniformMatrix4fv(m_locationModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void BasicShader::getUniforms()
{
    m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projectionView");
    m_locationModelMatrix = glGetUniformLocation(m_id, "model");
}