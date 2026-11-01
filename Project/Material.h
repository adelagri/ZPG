#pragma once
#include <glm/glm.hpp>

// defines the material coefficients in fragment shader, as well as the shininess factor for specular highlights
struct Material
{
	float ambient = 1.0f;
	float diffuse = 1.0f;
	float specular = 1.0f;
	float shininess = 32.0f;	// How shiny the material is (specular exponent)
};