#version 330 core
// Specify out variable
out vec4 FragColor;

in vec3 vColor;
in vec2 texCoord;

// This receives texture object
// sampler used to get fragment color from texture
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    // FragColor = vec4(vColor, 1.0);
    // texture function samples texture color
    // FragColor = texture(texture1, texCoord);

    // mix is used to interpolate color between multiple textures
    // the third argument decides in which proportions interpolation will
    // be done
    // FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}