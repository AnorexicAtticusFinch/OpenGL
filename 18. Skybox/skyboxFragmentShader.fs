#version 330 core

in vec3 texCoords;

out vec4 fragCol;

uniform samplerCube tex1;

void main()
{
    fragCol = texture(tex1, texCoords);
}