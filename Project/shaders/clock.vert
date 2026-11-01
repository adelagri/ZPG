/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#version 400

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float hourAngle;
uniform float minuteAngle;
uniform float secondAngle;

out vec3 vertexColor;
out vec3 worldPosition;
out vec3 worldNormal;

vec3 rotateZ(vec3 p, float a)
{
    float c = cos(a);
    float s = sin(a);
    return vec3(c * p.x - s * p.y, s * p.x + c * p.y, p.z);
}

bool sameColor(vec3 a, vec3 b)
{
    return distance(a, b) < 0.1;
}

void main()
{
    vec4 temp = modelMatrix * vec4(position,1.0f);
    worldPosition = temp.xyz / temp.w;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNormal = normalize(normalMatrix * normal);

    vec3 pos = position;
    vec3 newColor = color;

    if (sameColor(color, vec3(1.0, 0.0, 0.0))) // red
    {
        pos = rotateZ(pos, secondAngle);
        newColor = vec3(1.0, 0.0, 0.0); // Set the color to red
    }
    else if (sameColor(color, vec3(0.0, 1.0, 0.0))) // green
    {
        pos = rotateZ(pos, minuteAngle);
        newColor = vec3(0.0, 0.0, 0.0); // Set the color to black
    }
    else if (sameColor(color, vec3(0.0, 0.0, 1.0))) // blue
    {
        pos = rotateZ(pos, hourAngle);
        newColor = vec3(0.0, 0.0, 0.0); // Set the color to black
    }
    else if (sameColor(color, vec3(1.0, 1.0, 0.0))) // yellow
    {
        newColor = vec3(0.05, 1.95, 2.22); // Set the color to cyan
    }
    else if (sameColor(color, vec3(0.0, 0.0, 0.0))) // black
    {
        newColor = vec3(0.5, 0.5, 0.5); // Set the color to gray
    }
    else if (sameColor(color, vec3(1.0, 1.0, 1.0))) // white
    {
        newColor = vec3(1.0, 1.0, 1.0); // Set the color to white
    }

    vertexColor = newColor;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}