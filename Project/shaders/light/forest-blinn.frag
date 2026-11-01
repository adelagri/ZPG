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

out vec4 fragColor;

// Point light attenuation calculation
float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att = 1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}

void main()
{
    vec3 lightToVector = normalize(lightPosition - worldPosition);

    vec3 viewDir = normalize(cameraPosition - worldPosition);

    vec3 n = normalize(worldNormal);
    vec3 h = normalize(lightToVector + viewDir);

    float dotProduct = dot(lightToVector, n);

    float Is = 0.0;
    if (dotProduct > 0.0) {
        Is = pow(max(dot(n, h), 0.0), shininess);
    }

    float dist = distance(lightPosition, worldPosition);
    float att = attenuation(dist, attConstant, attLinear, attQuadratic);

    vec3 Ia = vec3(0.05) * vertexColor;
    vec3 Id = dotProduct * vertexColor;

    // I = Ia (ambient) + Id (diffuse) + Is (specular)
    fragColor = vec4(att * (Ia * material.x + Id * material.y + Is * material.z), 1.0); // Apply attenuation to the final color - depends on the intended use case
}