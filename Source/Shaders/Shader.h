#ifndef SHADER_H
#define SHADER_H 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
    public:
        // Constructors reads and builds the shader
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader() = default;

        // Use/activate shader
        void use();
        // Utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const; 
        void setFloat(const std::string& name, float value) const;
        GLuint getID() const;

    protected:
        virtual void getUniforms() = 0;
        // Program ID
        GLuint m_id;
};

#endif