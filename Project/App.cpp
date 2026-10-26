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

	/*
	// Clock scene with a clock model
	Scene* scene2 = new Scene();
	ShaderProgram* clockShader = scene2->AddShader("shaders/clock.vert", "shaders/default.frag");
	camera.Attach(clockShader);

	Model* clockMod = scene2->AddModel(
		clockModel, sizeof(clockModel) / (sizeof(float) * LAYOUT_POS_NORMAL_COLOR.floatsPerVertex),
		LAYOUT_POS_NORMAL_COLOR);

	auto clockTransform = std::make_shared<TransformationComposite>();
	clockTransform->Add(std::make_shared<Scale>(glm::vec3(-1.0f, 1.0f, 1.0f)));
	DrawableObject* clockObj1 = new DrawableObject(clockMod, clockShader, clockTransform);
	scene2->AddObject(clockObj1);
	scenes.push_back(scene2);

	
	// Forest scene with trees and bushes
	Scene* scene3 = new Scene();

	ShaderProgram* treeShader = scene3->AddShader("shaders/tree.vert", "shaders/tree.frag");
	ShaderProgram* bushShader = scene3->AddShader("shaders/bush.vert", "shaders/bush.frag");
	ShaderProgram* groundShader = scene3->AddShader("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader = scene3->AddShader("shaders/login.vert", "shaders/default.frag");

	camera.Attach(treeShader);
	camera.Attach(bushShader);
	camera.Attach(groundShader);
	camera.Attach(loginShader);

	Model* treeModel = scene3->AddModel(
		tree, sizeof(tree) / (sizeof(float) * LAYOUT_POS_NORMAL.floatsPerVertex),
		LAYOUT_POS_NORMAL);

	Model* bushModel = scene3->AddModel(
		bushes, sizeof(bushes) / (sizeof(float) * LAYOUT_POS_NORMAL.floatsPerVertex),
		LAYOUT_POS_NORMAL);

	Model* groundModel = scene3->AddModel(
		ground, sizeof(ground) / (sizeof(float) * LAYOUT_POS_COLOR.floatsPerVertex),
		LAYOUT_POS_COLOR);

	Model* loginModel = scene3->AddModel(
		login, sizeof(login) / (sizeof(float) * LAYOUT_POS_NORMAL.floatsPerVertex),
		LAYOUT_POS_NORMAL);

	for (int i = 0; i < 74; i++) {
		float x = RandomFloat(-30.0f, 30.0f);
		float z = RandomFloat(-0.8f, 20.0f);

		float angle = RandomFloat(0.0f, 359.0f);	// random rotation angle in degrees
		float scale = RandomFloat(0.5f, 1.2f);

		auto treeTransform = std::make_shared<TransformationComposite>();
		treeTransform->Add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
		treeTransform->Add(std::make_shared<Rotation>(angle, glm::vec3(0, 1, 0)));
		treeTransform->Add(std::make_shared<Scale>(glm::vec3(scale)));

		DrawableObject* treeObj = new DrawableObject(treeModel, treeShader, treeTransform);

		scene3->AddObject(treeObj);
	}

	for (int i = 0; i < 60; i++) {
		float x = RandomFloat(-30.0f, 30.0f);
		float z = RandomFloat(-0.8f, 20.0f);

		float angle = RandomFloat(0.0f, 359.0f);	// random rotation angle in degrees
		float scale = RandomFloat(0.8f, 2.0f);

		auto bushTransform = std::make_shared<TransformationComposite>();
		bushTransform->Add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
		bushTransform->Add(std::make_shared<Rotation>(angle, glm::vec3(0, 1, 0)));
		bushTransform->Add(std::make_shared<Scale>(glm::vec3(scale)));

		DrawableObject* bushObj = new DrawableObject(bushModel, bushShader, bushTransform);

		scene3->AddObject(bushObj);
	}

	auto groundTransform = std::make_shared<TransformationComposite>();
	groundTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, 0.0f, 0.0f)));
	groundTransform->Add(std::make_shared<Rotation>(90.0f, glm::vec3(1, 0, 0))); // rotate the ground to be horizontal
	groundTransform->Add(std::make_shared<Scale>(glm::vec3(60.0f)));

	DrawableObject* groundObj = new DrawableObject(groundModel, groundShader, groundTransform);
	scene3->AddObject(groundObj);

	auto loginTransform = std::make_shared<TransformationComposite>();
	loginTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, 1.0f, -5.0f)));
	loginTransform->Add(std::make_shared<Scale>(glm::vec3(1.0f)));

	DrawableObject* loginObj = new DrawableObject(loginModel, loginShader, loginTransform);
	scene3->AddObject(loginObj);


	// Add the clock model to the forest scene with different transformations
	auto clockTransform2 = std::make_shared<TransformationComposite>();
	clockTransform2->Add(std::make_shared<Translation>(glm::vec3(2.0f, 3.0f, -1.0f)));
	clockTransform2->Add(std::make_shared<Scale>(glm::vec3(-0.5f, 0.5f, 0.5f)));
	scene3->AddObject(new DrawableObject(clockMod, clockShader, clockTransform2));

	auto clockTransform3 = std::make_shared<TransformationComposite>();
	clockTransform3->Add(std::make_shared<Translation>(glm::vec3(-2.0f, 3.0f, 2.0f)));
	clockTransform3->Add(std::make_shared<Rotation>(60.0f, glm::vec3(0, 1, 0)));
	clockTransform3->Add(std::make_shared<Scale>(glm::vec3(-0.5f, 0.5f, 0.5f)));
	scene3->AddObject(new DrawableObject(clockMod, clockShader, clockTransform3));

	scenes.push_back(scene3);

	this->clockShader = clockShader;	// store the clock shader for updating the clock hands in the main loop
	*/

	// Sphere scene with light shader used
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
	camera.SetRatio((float)width / (float)height);
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
