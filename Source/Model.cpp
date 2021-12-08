#include "Model.h"

void Model::construct(const std::vector<GLfloat>& vertexPositions, 
                      const std::vector<GLfloat>& textureCoords,
                      const std::vector<GLuint>& indices)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    addVBO(vertexPositions, 3);
    addVBO(textureCoords, 2);
    addEBO(indices);
}

void Model::addVBO(const std::vector<GLfloat>& data, int dim)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(m_vboCount, dim, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(m_vboCount++);    
}

void Model::addEBO(const std::vector<GLuint>& indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}