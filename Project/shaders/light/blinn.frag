/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPosition;

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
    vec3 lightPosition = vec3(0.0); //Point Light position

    vec3 lightToVector = normalize(lightPosition - worldPosition);
    vec3 viewVector = normalize(cameraPosition - worldPosition);

    vec3 n = normalize(worldNormal);
    vec3 h = normalize(lightToVector + viewVector);

    float dotProduct = dot(lightToVector, n);

    float Is = 0.0;
    if (dotProduct > 0.0) {
        Is = pow(max(dot(n, h), 0.0), 32.0);
    }
    
    vec4 objectColor = vec4( 0.385, 0.647, 0.812, 1.0);

    vec4 Id = max(dotProduct, 0.0) * objectColor;
    vec4 Ia = vec4( 0.1, 0.1, 0.1, 1.0);

    fragColor = Ia + Id + (Is * vec4(1.0));
}