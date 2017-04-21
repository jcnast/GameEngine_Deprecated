/*
#pragma once

#include "ContextInfo.h"
#include "../Core/Init/FrameBufferInfo.h"
#include "../Core/Init/WindowInfo.h"
#include "../Core/Init/InitGlew.h"
#include "ProgramManager.h"

namespace Managers
{
	class WindowManager
	{
	private:
		static WindowManager* Instance;

		// set up callbacks or something for the windows HWND class to track it's status (active, focused...)
		static HWND ActiveWindow;

		WindowManager();
	public:
		~WindowManager();
		static WindowManager* GetInstance();

	private:
		// constant callbacks from windows
		//static LRESULT WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

		static void SetFocused(bool focused);
		static void SetActive(bool active);
	};
}

*/