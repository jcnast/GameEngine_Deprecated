#pragma once

namespace Engine
{
	namespace EngineManagers
	{
		class EngineManager;
	}
}

namespace Managers
{
	class InputManager
	{
	private:
		static InputManager* Instance;
		static Engine::EngineManagers::EngineManager* EngineManager;

		static int LastX;
		static int LastY;

		InputManager();

	public:
		~InputManager();
		static InputManager* GetInstance();

		static void SetEngineManager(Engine::EngineManagers::EngineManager* engineManager);

		static void NotifyMouseMovement(int x, int y);
		static void NotifyMouseClick(int button, int state, int x, int y);
		static void NotifyKeyboardClick(unsigned char key, int x, int y);
	};
}