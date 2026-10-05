/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <glad/gl.h> 

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "Scene.h"

#include "triangle.h"
#include "square.h"
#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class App
{
public:
	App();
	~App();

	static void GetVersionInfo();
	void Run();

private:
	GLFWwindow* Window;
	int Width, Height;
	float Ratio;

	std::vector<Scene*> scenes;
	int currentSceneIndex = 0;

	void InitScenes();

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void WindowFocusCallback(GLFWwindow* window, int focused);
	static void WindowIconifyCallback(GLFWwindow* window, int iconified);
	static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	static void CursorCallback(GLFWwindow* window, double x, double y);
	static void ButtonCallback(GLFWwindow* window, int button, int action, int mode);

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 ModelMatrix;

	// příznaky, jestli je klávesa právě držená (pro plynulý pohyb)
	bool rotateLeftPressed = false;
	bool rotateRightPressed = false;
};

