/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vertexColor = color;
    vertexNormal = normal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}