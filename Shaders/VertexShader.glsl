// OpenGL version and profile
#version 330 core 
// Specify all attributes of input vertices
// Here we're only interested n position
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;

out vec3 vColor;

void main()
{
    // gl_Position ia a predefined variable
    // This will be output data of vertex shader
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
    vColor = aColor;
}