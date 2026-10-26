/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 vertexColor;

uniform vec3 cameraPosition;

out vec4 fragColor;

void main()
{
    vec3 Ia = vec3(0.1, 0.1, 0.1);
    fragColor = vec4(Ia, 1.0);
}