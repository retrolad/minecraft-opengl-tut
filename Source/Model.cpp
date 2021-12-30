#include "Model.h"

#include "Utils/rtexcept.h"

Model::Model(const Mesh& mesh)
{
    construct(mesh);
}

Model::~Model()
{
    deleteData();
}

Model::Model(Model&& other)
:   m_vao           (other.m_vao)
,   m_vboCount      (other.m_vboCount)
,   m_indicesCount  (other.m_indicesCount)
,   m_buffers       (std::move(other.m_buffers))
{ 
    other.m_vao             = 0;
    other.m_vboCount        = 0; 
    other.m_indicesCount    = 0;
}

Model& Model::operator=(Model&& other)
{
    m_vao = other.m_vao;
    m_vboCount = other.m_vboCount;
    m_indicesCount = other.m_indicesCount;
    m_buffers = std::move(other.m_buffers);

    other.m_vao             = 0;
    other.m_vboCount        = 0;
    other.m_indicesCount    = 0;

    return *this;
}

void Model::construct(const Mesh& mesh)
{
    if(m_vao != 0)
        deleteData();

    GL(glGenVertexArrays(1, &m_vao));
    GL(glBindVertexArray(m_vao));

    addVBO(mesh.vertexPositions, 3);
    addVBO(mesh.textureCoords, 2);
    addEBO(mesh.indices);

    m_indicesCount = mesh.indices.size();
}

void Model::addVBO(const std::vector<GLfloat>& data, int dim)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(m_vboCount, dim, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(m_vboCount++);    

    m_buffers.push_back(vbo);
}

void Model::addEBO(const std::vector<GLuint>& indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

int Model::getIndicesCount() const
{
    return m_indicesCount;
}

void Model::bindVAO() const
{
    glBindVertexArray(m_vao);
}

void Model::deleteData()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(m_buffers.size(), m_buffers.data());

    m_buffers.clear();

    m_vboCount     = 0;
    m_vao          = 0;
    m_indicesCount = 0;
}
