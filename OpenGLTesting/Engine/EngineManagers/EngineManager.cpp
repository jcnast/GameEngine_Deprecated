#include "EngineMananger.h"

#include "../General/Camera.h"
#include "../Rendering/RenderingManagers/RenderManager.h"
#include "../Rendering/RenderingManagers/ShaderManager.h"

#include "../../Dependencies/freeglut/freeglut.h"
#include "../../Dependencies/freeglut/glut.h"

using namespace Engine;
using namespace EngineManagers;

using namespace Engine::Rendering;
using namespace Rendering::RenderManagers;

EngineManager::EngineManager()
{
	Camera = new Engine::Camera(1, 1, glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f, -10.0f, -10.0f));
	SetUpCamera(1, 1);

	RenderManager = new RenderManagers::RenderManager();
	ShaderManager = new RenderManagers::ShaderManager();

	ShaderManager->CreateProgram("Default", "Engine\\Rendering\\Shaders\\VertexShader.glsl", "Engine\\Rendering\\Shaders\\FragmentShader.glsl");

	// test stuff, to be removed
	RenderManager->AddStaticModel(ShaderManager->GetShader("Default"), "MI\\MI.obj", "Models\\MI\\MI.bmp");
	RenderManager->AddSprite(ShaderManager->GetShader("Default"), "Sprites\\Logo\\Logo.bmp");
}

EngineManager::~EngineManager()
{
	delete RenderManager;
	delete ShaderManager;
}

void EngineManager::SetUpCamera(int width, int height)
{
	Camera->SetAspectRatio(width, height);
}

void EngineManager::Update(float deltaTime)
{
	RenderManager->Update();
}

void EngineManager::KeyboardInput(unsigned char key, int x, int y)
{
	std::cout << "BUTTON: " << key << ", AT: " << x << ", " << y << std::endl;
}

void EngineManager::MouseClick(int button, int state, int x, int y)
{
	std::cout << "MOUSE CLICKED AT: " << x << ", " << y << ", BUTTON: " << button << ", STATE: " << state << std::endl;
}

void EngineManager::MouseMove(int x, int y)
{
	std::cout << "MOUSE MOVED TO: " << x << ", " << y << std::endl;
}

void EngineManager::NotifyBeginFrame()
{
	// nothing yet
}

void EngineManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

	RenderManager->Draw(Camera->GetRenderMatrix(), glm::vec4(1.0f));
	// UIManager->Draw(SceneCamera->GetOrthographicMatrix(), glm::vec4(1.0f));

	glutSwapBuffers();
}

void EngineManager::NotifyEndFrame()
{
	// nothing yet
}

void EngineManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	SetUpCamera(width, height);
}