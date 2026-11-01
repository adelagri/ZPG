/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "App.h"

static float RandomFloat(float min, float max)
{
	float t = rand() / (float)RAND_MAX;   // number between 0 and 1
	return min + t * (max - min);
}

App::App()
{
	// Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(1200, 1000, "ZPG", NULL, NULL);	// create a window and its OpenGL context
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// make the window's context current
	// this is necessary before calling any OpenGL functions, otherwise they will not work
	// needs to be called before glfwGetProcAddress - requires a current context to work
	glfwMakeContextCurrent(window);

	// Set the swap interval to 1
	// the screen will be updated at the same rate as the monitor's refresh rate
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers - GLAD manages function pointers for OpenGL so we can use modern OpenGL functions
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))	// glfwGetProcAddress returns the address of the specified OpenGL function, which is then passed to gladLoadGL to load the function pointers
	{
		printf("GLAD initialization failed\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(window, this);	// set the user pointer for the window to this instance of the App class, so we can access it in the callbacks

	// Sets the key callback
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorCallback);
	glfwSetMouseButtonCallback(window, ButtonCallback);
	glfwSetWindowFocusCallback(window, WindowFocusCallback);
	glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
	glfwGetFramebufferSize(window, &width, &height);

	camera.SetRatio(width / (float)height);

	glViewport(0, 0, width, height);

	// Model matrix : an identity matrix (model will be at the origin)
	ModelMatrix = glm::mat4(1.0f);
}

App::~App()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::GetVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void App::Run()
{
	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.

	InitScenes();

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		auto deltaTime = static_cast<float>(now - lastTime);
		lastTime = now;

		Scene& currentScene = *scenes[currentSceneIndex];
		currentScene.Update(deltaTime);

		float forward = 0.0f, right = 0.0f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) forward += 1.0f;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) forward -= 1.0f;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) right += 1.0f;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) right -= 1.0f;

		const float speed = 3.0f;	// camera movement speed

		camera.Move(forward * speed * deltaTime, right * speed * deltaTime);

		glm::vec3 c = currentScene.ClearColor();
		glClearColor(c.r, c.g, c.b, 1.0f);
		
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentScene.Draw();

		// Display the rendered frame and process events
		glfwSwapBuffers(window); // back buffer becomes front buffer and is displayed on the screen, front buffer becomes back buffer and is used for rendering the next frame
		glfwPollEvents();	// process events, call callbacks (applies for the next frame)
	}
}

void App::InitScenes()
{	
	scenes.push_back(std::make_unique<SolarSystemScene>(camera));
	scenes.push_back(std::make_unique<SphereScene>(camera));
	scenes.push_back(std::make_unique<ForestScene>(camera));
}

void App::ErrorCallback(int error, const char* description) { fputs(description, stderr); }

void App::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

	// scene switching
	if (action == GLFW_PRESS) {
		int newIndex = -1;
		if (key == GLFW_KEY_1) newIndex = 0;
		if (key == GLFW_KEY_2) newIndex = 1;
		if (key == GLFW_KEY_3) newIndex = 2;
		if (key == GLFW_KEY_4) newIndex = 3;

		if (newIndex >= 0 && newIndex < (int)app->scenes.size())
			app->currentSceneIndex = newIndex;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void App::WindowFocusCallback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void App::WindowIconifyCallback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void App::WindowSizeCallback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	app->OnResize(width, height);
}

void App::CursorCallback(GLFWwindow* window, double x, double y) 
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	app->OnCursor(x, y);
}

void App::ButtonCallback(GLFWwindow* window, int button, int action, int mode) {
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	app->OnMouse(button, action);
}

void App::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
	//camera.SetRatio((float)width / (float)height);
	glViewport(0, 0, width, height);

}

void App::OnMouse(int button, int action)
{
	if (button != GLFW_MOUSE_BUTTON_RIGHT) return;
	looking = (action == GLFW_PRESS);
	if (looking) {
		glfwGetCursorPos(window, &lastX, &lastY);
	}
}

void App::OnCursor(double x, double y)
{
	if (!looking) return;

	const float sensitivity = 0.1f;
	auto dx = static_cast<float>(x - lastX);
	auto dy = static_cast<float>(y - lastY);
	lastX = x;
	lastY = y;

	camera.Rotate(dx * sensitivity, -dy * sensitivity);
}
