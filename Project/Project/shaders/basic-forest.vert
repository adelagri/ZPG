/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform float angle;
uniform vec3 translation;
uniform vec3 scale;

uniform int rotationAxis; // 0 for x-axis, 1 for y-axis, 2 for z-axis

vec3 rotate(vec3 pos, float a, int axis) 
{
    float c = cos(a);
    float s = sin(a);

    vec3 rotated;

    if (axis == 0) { // rotation around x-axis
        rotated.x = pos.x;
        rotated.y = c * pos.y - s * pos.z;
        rotated.z = s * pos.y + c * pos.z;
    } 
    else if (axis == 1) { // rotation around y-axis
        rotated.x = c * pos.x + s * pos.z;
        rotated.y = pos.y;
        rotated.z = -s * pos.x + c * pos.z;
    } 
    else if (axis == 2) { // rotation around z-axis
        rotated.x = c * pos.x - s * pos.y;
        rotated.y = s * pos.x + c * pos.y;
        rotated.z = pos.z;
    } 
    else {
        rotated = pos; // no rotation if axis is invalid
    }
    return rotated;
}

void main()
{
    // 1. change of scale
    vec3 scaled = position * scale;

    // 2. rotation
    vec3 rotated = rotate(scaled, angle, rotationAxis);

    // 3. translation
    vec3 finalPosition = rotated + translation;

    vertexColor = color;
    gl_Position = vec4(finalPosition * 0.1 - vec3(0.0f, 0.5f, 0.0f), 1.0);   // scale down the position and move it down by 0.5 units in the y-axis
}