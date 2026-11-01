/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 position;
in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;
out vec3 worldPosition;
out vec3 worldNormal;

void main()
{
    vec4 temp = modelMatrix * vec4(position,1.0f);
    worldPosition = temp.xyz / temp.w;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNormal = normalize(normalMatrix * normal);

    vec3 color = vec3(0, 0, 0);
    
    if (gl_VertexID > 36443) 
    {
        color = vec3(0.f, 1.f, 0.f);
    }
    else 
    {
        color = vec3(1.f, 0.f, 0.f);
    }

    vertexColor = color;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}