/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

out vec4 fragColor;

void main()
{
    vec3 lightToVector = normalize(lightPosition - worldPosition);
    vec3 viewVector = normalize(cameraPosition - worldPosition);

    vec3 n = normalize(worldNormal);
    vec3 h = normalize(lightToVector + viewVector);

    float dotProduct = max(dot(lightToVector, n), 0.0);
    vec4 objectColor = vec4(vertexColor, 1);

    vec4 Id = dotProduct * objectColor;
    vec4 Ia = vec4(0.0);
    float Is = pow(max(dot(n, h), 0.0), 32.0);

    fragColor = Ia + Id + (Is * vec4(1.0));
}