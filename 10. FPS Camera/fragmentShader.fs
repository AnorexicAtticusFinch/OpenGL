#version 330 core

in vec2 texCoord;

out vec4 frag_color;

uniform sampler2D textureImage1;
uniform sampler2D textureImage2;
uniform float mixVal;

void main()
{
    frag_color = mix(texture(textureImage1, texCoord), texture(textureImage2, texCoord), mixVal);
}