/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 position;   // vertex position
in vec3 normal;   // vertex normal

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPosition;
out vec3 worldNormal;

void main()
{
    vec4 temp = modelMatrix * vec4(position,1.0f);
    worldPosition = temp.xyz / temp.w;
    worldNormal = normal; //next lesson

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position,1.0f);
}