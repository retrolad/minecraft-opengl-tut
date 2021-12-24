#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Utils/Text.h"
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
        
        void addText(const Text& text);

        void render();
    private:
        std::map<char, Character> m_characters;
        std::vector<Text> m_texts;
        GLuint m_VAO;
        GLuint m_VBO;

        TextShader m_shader;
};

#endif // TEXTRENDERER_H
