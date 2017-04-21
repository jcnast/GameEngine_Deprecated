#pragma once

#include "../Engine/EngineManagers/EngineMananger.h"

namespace Managers
{
	class InputManager;
	class TimeManager;

	class ProgramManager
	{
	private:
		static ProgramManager* Instance;

	// managers
		Managers::TimeManager* TimeManager;
		Engine::EngineManagers::EngineManager* EngineManager;
		Managers::InputManager* InputManager;

		ProgramManager();

	public:
		~ProgramManager();
		static ProgramManager* GetInstance();

		// persistent methods
		virtual void NotifyUpdate();

		// constant methods
		virtual void NotifyRender();
		virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);
	};
}