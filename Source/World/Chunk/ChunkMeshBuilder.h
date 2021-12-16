#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

class ChunkSection;
class ChunkMesh;

class ChunkMeshBuilder 
{
    public:
        ChunkMeshBuilder(ChunkSection& chunk);

        void buildMesh(ChunkMesh& mesh);

        private:
            ChunkSection* m_pChunk;
            ChunkMesh*    m_pMesh;
};

#endif 