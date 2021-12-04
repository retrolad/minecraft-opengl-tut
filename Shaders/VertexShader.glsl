// OpenGL version and profile
#version 330 core 
// Specify all attributes of input vertices
// Here we're only interested n position
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float xOffset;
uniform mat4 transform;

out vec3 vColor;
out vec2 texCoord;

void main()
{
    // gl_Position ia a predefined variable
    // This will be output data of vertex shader
    gl_Position = transform * vec4(aPos, 1.0);
    vColor = aColor;
    texCoord = aTexCoord;
}