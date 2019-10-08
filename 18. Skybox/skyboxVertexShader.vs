#version 330 core

layout (location = 0) in vec3 inPos;

out vec3 texCoords;

uniform mat4 transform;

void main()
{
    gl_Position = (transform * vec4(inPos, 1.0f)).xyww;
    texCoords = inPos;
}