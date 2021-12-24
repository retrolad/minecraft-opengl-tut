#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <string>
#include <glm/glm.hpp>

#include "../Shaders/TextShader.h"

struct Character
{
    unsigned int textureID; // ID of glyph texture object
    glm::ivec2   size;      // Size of glyph
    glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
    unsigned int advance;   // Offset from prev next glyph?
};

class TextRenderer
{
    public:
        TextRenderer();

        void load(std::string font, unsigned int fontSize);

        void render(const std::string& text, float x, float y, float scale, const glm::vec3& color);
    private:
        std::map<char, Character> m_characters;
        GLuint m_VAO;
        GLuint m_VBO;

        TextShader m_shader;
};

#endif // TEXTRENDERER_H
