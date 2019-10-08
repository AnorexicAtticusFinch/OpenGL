#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 final_color;

uniform sampler2D tex1;
uniform samplerCube tex2;
uniform vec3 camPos;

void main()
{

    vec3 norm = normalize(normal);

    vec3 incident = normalize(fragPos - camPos);
    vec3 reflect = reflect(incident, norm);
    
    float airToGlass = 1.0 / 1.52;
    vec3 refract = refract(incident, norm, airToGlass);

    //final_color = texture(tex1, texCoords);
    //final_color = texture(tex2, reflect);
    final_color = texture(tex2, refract);
    
}