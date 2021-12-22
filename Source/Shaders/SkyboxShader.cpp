#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(const std::string& vertexPath,
                            const std::string& fragmentPath)
: Shader(vertexPath, fragmentPath)
{
    getUniforms();
}

void SkyboxShader::setProjectionMatrix(const glm::mat4& projMatrix)
{
    glUniformMatrix4fv(m_locationProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
}

void SkyboxShader::setViewMatrix(glm::mat4 viewMatrix)
{
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    glUniformMatrix4fv(m_locationViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void SkyboxShader::getUniforms()
{
    m_locationProjectionMatrix = glGetUniformLocation(m_id, "projection");
    m_locationViewMatrix       = glGetUniformLocation(m_id, "view");
}
