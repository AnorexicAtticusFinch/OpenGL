#version 330 core

in vec4 frag_color_in;

out vec4 frag_color;

uniform float timeVal;

void main()
{
    frag_color = vec4(frag_color_in.x * timeVal, frag_color_in.y * timeVal, frag_color_in.z * timeVal, frag_color_in.w);
}