#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../Model.h"
#include "../Mesh.h"

class ChunkMesh
{
    public:
        ChunkMesh();

        void addFace(const Mesh& mesh);
    private:
        Mesh m_mesh;
        Model m_model;
};

#endif