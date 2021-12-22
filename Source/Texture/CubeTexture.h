#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include "../Utils/NonCopyable.h"

#include <glad/glad.h>
#include <vector>
#include <string>

class CubeTexture : public NonCopyable
{
    public:
        CubeTexture() = default;
        CubeTexture(const std::vector<std::string>& faces);

        ~CubeTexture();

        void loadCubemap();

        void bindTexture() const;

    private:
        GLuint m_id;
        std::vector<std::string> m_faces;
};

#endif // CUBETEXTURE_H
