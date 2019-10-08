#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 final_color;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform float specularStrength;
uniform int specularSharpness;
uniform vec3 camPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = dot(norm, lightDir);
    diffuse = max(diffuse, 0.0f);

    vec3 camDir = normalize(camPos - fragPos);
    vec3 reflectedLightDir = reflect(-lightDir, norm);

    float specular = dot(camDir, reflectedLightDir);
    specular = max(specular, 0.0f);
    specular = pow(specular, specularSharpness);
    specular = specularStrength * specular;

    vec3 resultLight = (ambientStrength + diffuse + specular) * lightColor;

    final_color = vec4(resultLight * objectColor, 1.0f);
}