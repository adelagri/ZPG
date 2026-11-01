#pragma once

#include "ShaderProgram.h"

class ClockHands
{
public:
	static void Update(ShaderProgram* shader);	// Reads the current local time and updates the shader uniforms for the clock hands' rotation angles
};

