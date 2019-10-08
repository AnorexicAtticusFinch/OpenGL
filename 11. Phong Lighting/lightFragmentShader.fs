#version 330 core

out vec4 final_color;

uniform vec3 lightColor;

void main()
{
    final_color = vec4(lightColor, 1.0f);
}