#include "ProgramManager.h"

#include "InputManager.h"
#include "TimeManager.h"

#include "../Dependencies/freeglut/freeglut.h"
#include "../Dependencies/freeglut/glut.h"

using namespace Managers;

ProgramManager* ProgramManager::Instance = nullptr;

ProgramManager::ProgramManager()
{
	glEnable(GL_DEPTH_TEST);

	TimeManager = new Managers::TimeManager();
	EngineManager = new Engine::EngineManagers::EngineManager();
	InputManager = Managers::InputManager::GetInstance();

	InputManager->SetEngineManager(EngineManager);
}

ProgramManager::~ProgramManager()
{
	delete TimeManager;
	delete InputManager;
	delete EngineManager;
}

ProgramManager* ProgramManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new ProgramManager();
	}
	return Instance;
}

void ProgramManager::NotifyUpdate()
{
	// get dt from time manager
	// update game
	float DeltaTime = TimeManager->GetDeltaTime();
	EngineManager->Update(DeltaTime);
}

void ProgramManager::NotifyRender()
{
	EngineManager->NotifyBeginFrame();
	EngineManager->NotifyDisplayFrame();

	glutSwapBuffers();

	EngineManager->NotifyEndFrame();
}

void ProgramManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	EngineManager->NotifyReshape(width, height, previousWidth, previousHeight);
}