// OpenGL version and profile
#version 330 core 
// Specify all attributes of input vertices
// Here we're only interested n position
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

uniform float xOffset;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection; 

out vec2 texCoord;
out vec3 vColor;

void main()
{
    // gl_Position ia a predefined variable
    // This will be output data of vertex shader
    gl_Position = vec4(aPos, 1.0f);

    // gl_Position = projection * view * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    vColor = aColor;
}