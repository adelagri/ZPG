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

uniform vec3 material;
uniform float shininess;

uniform float attConstant;
uniform float attLinear;
uniform float attQuadratic;

float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att = 1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}

out vec4 fragColor;

void main()
{
    vec3 lightToVector = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    vec3 n = normalize(worldNormal);
    vec3 h = normalize(lightToVector + viewDir);

    float dotProduct = max(dot(lightToVector, n), 0.0);

    vec3 Ia = vec3(0.1) * vertexColor;
    vec3 Id = dotProduct * vertexColor;
    float Is = pow(max(dot(n, h), 0.0), shininess);

    float dist = distance(lightPosition, worldPosition);
    float att = attenuation(dist, attConstant, attLinear, attQuadratic);

    fragColor = vec4(att * (Ia * material.x + Id * material.y + Is * material.z), 1.0);
}