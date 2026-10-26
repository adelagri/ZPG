/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 vertexColor;
in vec3 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

void main(void){
    vec3 lightPosition= vec3(0.0); //Point Light position
    vec3 lightToVector = normalize(lightPosition - worldPosition);

    vec3 n = normalize(worldNormal);

    vec4 Ia = vec4 (0.1 ,0.1 ,0.1 ,1.0);

    float Id = max (dot(lightToVector, n),0.0);

    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

    fragColor = Ia + (Id * objectColor);
}