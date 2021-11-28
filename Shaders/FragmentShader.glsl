#version 330 core
// Specify out variable
out vec4 FragColor;

in vec3 vColor;

void main()
{
    // FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    FragColor = vec4(vColor, 1.0);
}