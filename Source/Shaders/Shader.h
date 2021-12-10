#ifndef SHADER_H
#define SHADER_H 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
    // Constructors reads and builds the shader
    Shader(const std::string& vertexPath = "VertexShader", const std::string& fragmentPath = "FragmentShader");
    ~Shader() = default;

    // Use/activate shader
    void use();
    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const; 
    void setFloat(const std::string& name, float value) const;
    GLuint getID() const;

    void setProjectionViewMatrix(const glm::mat4& projMatrix);
    void setViewMatrix(const glm::mat4& viewMatrix);
    void setModelMatrix(const glm::mat4& modelMatrix);
private:
    // Program ID
    GLuint ID;
    GLint m_locationProjectionViewMatrix;
    GLint m_locationModelMatrix;
};

#endif