#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture
{
private:
    GLuint m_id;
    unsigned char* m_Buffer;
    std::string m_FilePath;
    int m_Width;
    int m_Height;
    // Number of color channels
    int m_BPP;
public:
    Texture() = default;
    Texture(const std::string& path);
    ~Texture();

    void loadFromFile(const std::string& path);

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

};

#endif