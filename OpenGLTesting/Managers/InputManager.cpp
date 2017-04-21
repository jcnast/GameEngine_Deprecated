#include "InputManager.h"

#include "../../Core/Init/InitGlut.h"
#include "../Engine/EngineManagers/EngineMananger.h"

#include "../../Dependencies/freeglut/freeglut.h"

#include <iostream>

using namespace Managers;

using namespace Engine;
using namespace Engine::EngineManagers;

InputManager* InputManager::Instance = nullptr;
EngineManager* InputManager::EngineManager = nullptr;

int InputManager::LastX = 0;
int InputManager::LastY = 0;

InputManager::InputManager()
{
	// set input callbacks
	glutPassiveMotionFunc(NotifyMouseMovement);
	glutMouseFunc(NotifyMouseClick);
	glutKeyboardFunc(NotifyKeyboardClick);
}

InputManager::~InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new InputManager();
	}
	return Instance;
}

void InputManager::SetEngineManager(Engine::EngineManagers::EngineManager* engineManager)
{
	EngineManager = engineManager;
}

void InputManager::NotifyMouseMovement(int x, int y)
{
	LastX = x;
	LastY = y;

	EngineManager->MouseMove(x, y);
}

void InputManager::NotifyMouseClick(int button, int state, int x, int y)
{
	EngineManager->MouseClick(button, state, x, y);
}

void InputManager::NotifyKeyboardClick(unsigned char key, int x, int y)
{
	EngineManager->KeyboardInput(key, x, y);
}