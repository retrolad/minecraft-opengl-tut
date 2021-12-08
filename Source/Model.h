#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <vector>

class Model
{
public:
    Model() = default;
    void construct(const std::vector<GLfloat>& vertexPositions, 
                   const std::vector<GLfloat>& textureCoords,
                   const std::vector<GLuint>& indices);
    void addVBO(const std::vector<GLfloat>& data, int dim);
    void addEBO(const std::vector<GLuint>& indices);
private:
    GLuint m_vao = 0;    
    int m_vboCount = 0;
};

#endif 