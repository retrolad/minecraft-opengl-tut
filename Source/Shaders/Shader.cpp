#include <stdexcept>
#include "Shader.h"
#include "../FileUtil.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    // Get shaders source code from files
    vertexCode = GetFileContent("../Shaders/" + vertexPath + ".glsl");
    fragmentCode = GetFileContent("../Shaders/" + fragmentPath + ".glsl");

    // Get 0-terminated source codes
    const GLchar* vsCode = vertexCode.c_str();
    const GLchar* fsCode = fragmentCode.c_str();

    // Shaders objects ID's
    GLuint vertexShaderID, fragmentShaderID;
    // Degun data
    GLint success;
    GLchar infoLog[512];

    // Create vertex shader
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader source code to the shader object
    glShaderSource(vertexShaderID, 1, &vsCode, 0);
    // Compile shader with the attached source
    glCompileShader(vertexShaderID);

    // Check for errors
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        throw std::runtime_error("Failed to compile vertex shader: " + std::string(infoLog));
    }

    // Create fragment shader
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach the shader source code to the shader object
    glShaderSource(fragmentShaderID, 1, &fsCode, 0);
    // Compile shader with the attached source
    glCompileShader(fragmentShaderID);

    // Check for errors
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        throw std::runtime_error("Failed to compile vertex shader: " + std::string(infoLog));
    }

    // We use object of shader program to link all shaders
    m_id = glCreateProgram();

    // Attach shaders to program and link together
    glAttachShader(m_id, vertexShaderID);
    glAttachShader(m_id, fragmentShaderID);
    glLinkProgram(m_id);

     // Check for errors
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    // glValidateProgram(m_id); the same?
    if(!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        throw std::runtime_error("Failed to link shader program: " + std::string(infoLog));
    }

     // Delete shader objets, as we don't need them anymore
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::use()
{
    // Set this program as current active shader program
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const 
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (GLint)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

GLuint Shader::getID() const
{
    return m_id;
}