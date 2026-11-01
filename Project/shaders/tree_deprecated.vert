/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 330 core

in vec3 position;
in vec3 normal;

out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec3 color = vec3(0, 0, 0);
    
    if (gl_VertexID > 36443) 
    {
        color = vec3(0.f, 1.f, 0.f);
    }
    else 
    {
        color = vec3(1.f, 0.f, 0.f);
    }

    vertexColor = color;
    vertexNormal = normal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}