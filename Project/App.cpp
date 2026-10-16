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

	Window = glfwCreateWindow(1200, 1000, "ZPG", NULL, NULL);	// create a window and its OpenGL context
	if (!Window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// make the window's context current
	// this is necessary before calling any OpenGL functions, otherwise they will not work
	// needs to be called before glfwGetProcAddress - requires a current context to work
	glfwMakeContextCurrent(Window);

	// Set the swap interval to 1
	// the screen will be updated at the same rate as the monitor's refresh rate
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers - GLAD manages function pointers for OpenGL so we can use modern OpenGL functions
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))	// glfwGetProcAddress returns the address of the specified OpenGL function, which is then passed to gladLoadGL to load the function pointers
	{
		printf("GLAD initialization failed\n");
		glfwDestroyWindow(Window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(Window, this);	// set the user pointer for the window to this instance of the App class, so we can access it in the callbacks

	// Sets the key callback
	glfwSetKeyCallback(Window, KeyCallback);
	glfwSetCursorPosCallback(Window, CursorCallback);
	glfwSetMouseButtonCallback(Window, ButtonCallback);
	glfwSetWindowFocusCallback(Window, WindowFocusCallback);
	glfwSetWindowIconifyCallback(Window, WindowIconifyCallback);
	glfwSetWindowSizeCallback(Window, WindowSizeCallback);

	glfwGetFramebufferSize(Window, &Width, &Height);
	Ratio = Width / (float)Height;
	glViewport(0, 0, Width, Height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-Ratio, Ratio, -1.f, 1.f, 1.f, -1.f);

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

	// Camera matrix
	View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	ModelMatrix = glm::mat4(1.0f);


	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
}

App::~App()
{
	for (Scene* s : scenes) {
		delete s;
	}

	glfwDestroyWindow(Window);
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
	InitScenes();
	//double lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(Window))
	{
		/*
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastFrameTime);
		lastFrameTime = currentTime;
		*/

		Scene* currentScene = scenes[currentSceneIndex];

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentScene->Draw();

		// Display the rendered frame and process events
		glfwSwapBuffers(Window); // back buffer becomes front buffer and is displayed on the screen, front buffer becomes back buffer and is used for rendering the next frame
		glfwPollEvents();	// process events, call callbacks (applies for the next frame)
	}
}

void App::InitScenes()
{
	// Solar system scene with sun, earth and moon
	Scene* scene1 = new Scene();
	ShaderProgram* shader1 = scene1->AddShader("shaders/basic.vert", "shaders/basic.frag");

	Model* sunModel = scene1->AddModel(sun, sizeof(sun) / (sizeof(float) * 9), 9);

	auto sunFrame = std::make_shared<TransformationComposite>();
	sunFrame->Add(std::make_shared<DynamicRotation>(5.0f, glm::vec3(0, 0, 1)));
	sunFrame->Add(std::make_shared<Translation>(glm::vec3(0.3f, 0.0f, 0.0f)));

	auto sunTransform = std::make_shared<TransformationComposite>();
	sunTransform->Add(sunFrame);
	sunTransform->Add(std::make_shared<DynamicRotation>(1.5f, glm::vec3(0, 0, 1)));
	sunTransform->Add(std::make_shared<Scale>(glm::vec3(0.10f, 0.10f, 0.10f)));
	DrawableObject* sunObj = new DrawableObject(sunModel, shader1, sunTransform);

	Model* earthModel = scene1->AddModel(earth, sizeof(earth) / (sizeof(float) * 9), 9);
	auto earthFrame = std::make_shared<TransformationComposite>();
	earthFrame->Add(sunFrame);
	earthFrame->Add(std::make_shared<DynamicRotation>(20.0f, glm::vec3(0, 0, 1)));
	earthFrame->Add(std::make_shared<Translation>(glm::vec3(0.5f, 0.0f, 0.0f)));
	
	auto earthTransform = std::make_shared<TransformationComposite>();
	earthTransform->Add(earthFrame);
	earthTransform->Add(std::make_shared<DynamicRotation>(330.0f, glm::vec3(0, 0, 1)));
	earthTransform->Add(std::make_shared<Scale>(glm::vec3(0.05f, 0.05f, 0.05f)));
	DrawableObject* earthObj = new DrawableObject(earthModel, shader1, earthTransform);

	Model* moonModel = scene1->AddModel(moon, sizeof(moon) / (sizeof(float) * 9), 9);
	auto moonFrame = std::make_shared<TransformationComposite>();
	moonFrame->Add(earthFrame);
	moonFrame->Add(std::make_shared<DynamicRotation>(30.0f, glm::vec3(0, 0, 1)));
	moonFrame->Add(std::make_shared<Translation>(glm::vec3(0.125f, 0.0f, 0.0f)));

	auto moonTransform = std::make_shared<TransformationComposite>();
	moonTransform->Add(moonFrame);
	moonTransform->Add(std::make_shared<DynamicRotation>(90.0f, glm::vec3(0, 0, 1)));
	moonTransform->Add(std::make_shared<Scale>(glm::vec3(0.0125f, 0.0125f, 0.0125f)));
	DrawableObject* moonObj = new DrawableObject(moonModel, shader1, moonTransform);

	scene1->AddObject(sunObj);
	scene1->AddObject(earthObj);
	scene1->AddObject(moonObj);
	scenes.push_back(scene1);

	
	// Forest scene with trees
	Scene* scene2 = new Scene();
	ShaderProgram* shader2 = scene2->AddShader("shaders/basic.vert", "shaders/basic.frag");
	Model* treeModel = scene2->AddModel(tree, sizeof(tree) / (sizeof(float) * 6), 6);
	for (int i = 0; i < 13; i++) {
		float x = RandomFloat(-0.8f, 0.8f);	// random x position in the range -0.8 to 0.8
		float z = RandomFloat(-0.8f, 0.8f);	// random z position in the range -0.8 to 0.8

		float angle = RandomFloat(0.0f, 6.28f);	// 0 to 2*PI radians
		float scale = RandomFloat(0.05f, 0.08f);	// random scale in the range 0.05 to 0.08

		auto treeTransform = std::make_shared<TransformationComposite>();
		treeTransform->Add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
		treeTransform->Add(std::make_shared<Rotation>(angle, glm::vec3(0, 1, 0)));
		treeTransform->Add(std::make_shared<Scale>(glm::vec3(scale, scale, scale)));

		DrawableObject* treeObj = new DrawableObject(treeModel, shader2, treeTransform);

		scene2->AddObject(treeObj);
	}

	scenes.push_back(scene2);

	Scene* scene3 = new Scene();
	ShaderProgram* shader3 = scene3->AddShader("shaders/basic.vert", "shaders/basic.frag");

	Model* clockMod = scene3->AddModel(clockModel, sizeof(clockModel) / (sizeof(float) * 9), 9);
	
	
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
	glViewport(0, 0, width, height);
}

void App::CursorCallback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void App::ButtonCallback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
