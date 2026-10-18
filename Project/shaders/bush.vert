/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec3 color = vec3(0.0f, 1.0f, 0.0f);

    vertexColor = color;
    vertexNormal = normal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}