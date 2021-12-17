#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../../Model.h"
#include "../../Maths/glm.h"

#include <vector>

class ChunkMesh
{
    public:
        ChunkMesh();

        void addFace(const std::vector<GLfloat>& blockFace,
                     const std::vector<GLfloat>& textureCoords,
                     const glm::ivec3&           chunkPositions,
                     const glm::ivec3&           blockPosition);

        void createModel();
        const Model& getModel() const;
        int getVerticesCount() const;

    private:
        Mesh  m_mesh;
        Model m_model;

        GLuint m_indiceIdx = 0;
        GLuint m_verticesCount = 0;
};

#endif