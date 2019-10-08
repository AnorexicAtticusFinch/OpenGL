#version 330 core

layout (points) in;

layout (triangle_strip, max_vertices = 5) out;

out vec4 inFragColor;

void main()
{
    inFragColor = vec4(0.5, 0.25, 0, 1);

    gl_Position = gl_in[0].gl_Position + 2 * vec4(-0.1, -0.1, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + 2 * vec4(0.1, -0.1, 0, 0);
    EmitVertex();

    inFragColor = vec4(1.0);

    gl_Position = gl_in[0].gl_Position + 2 * vec4(-0.1, 0.1, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + 2 * vec4(0.1, 0.1, 0, 0);
    EmitVertex();

    inFragColor = vec4(0.5, 0.25, 0, 1);

    gl_Position = gl_in[0].gl_Position + 2 * vec4(0.0, 0.2, 0, 0);
    EmitVertex();

    EndPrimitive();
}