/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float hourAngle;
uniform float minuteAngle;
uniform float secondAngle;

vec3 rotateZ(vec3 p, float a)
{
    float c = cos(a);
    float s = sin(a);
    return vec3(c * p.x - s * p.y, s * p.x + c * p.y, p.z);
}

bool sameColor(vec3 a, vec3 b)
{
    return distance(a, b) == 0;
}

void main()
{
    if (sameColor(color, vec3(0.0, 0.0, 0.0)))  // black
    {
        
    } else if (sameColor(color, vec3(1.0, 1.0, 1.0)))  // white
    {
        
    } else if (sameColor(color, vec3(1.0, 0.0, 0.0)))  // red
    {

    } else if (sameColor(color, vec3(0.0, 0.0, 1.0)))  // blue
    {

    } else if (sameColor(color, vec3(0.0, 1.0, 0.0)))  // green
    {
        
    } else if (sameColor(color, vec3(1.0, 1.0, 0.0)))  // yellow
    {
        
    } else if (sameColor(color, vec3(1.0, 0.5, 0.0)))  // orange
    {
        
    }

    vertexColor = color;
    vertexNormal = normal;

    gl_Position = modelMatrix * vec4(position, 1.0);
}