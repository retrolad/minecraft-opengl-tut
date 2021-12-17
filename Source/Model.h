#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model
{
public:
    Model() = default;
    Model(const Mesh& mesh);

    ~Model();
    
    void construct(const Mesh& mesh);

    void addVBO(const std::vector<GLfloat>& data, int dim);
    void addEBO(const std::vector<GLuint>& indices);
    void bindVAO() const;

    int getIndicesCount() const;

    void deleteData();
private:
    GLuint m_vao          = 0;    
    GLuint m_indicesCount = 0;
    int m_vboCount        = 0;
    std::vector<GLuint> m_buffers;
};

#endif 