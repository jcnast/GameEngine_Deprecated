#pragma once

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "InitGlew.h"
#include "../../Managers/ProgramManager.h"

namespace Core
{
	namespace Init
	{
		class InitGlut
		{
		private:
			static Managers::ProgramManager* ProgramManager;
			static Core::WindowInfo WindowInfo;
			//static RECT WindowRect;int len;

			static HWND ActiveWindow;

			static bool Running;

		public:
			static void Init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FrameBufferInfo& frameBufferInfo);
			static void Run();
			static void Close();

			void EnterFullscreen();
			void ExitFullscreen();

			static void SetProgramManager(Managers::ProgramManager*& programManager);
			static void PrintOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo);

		private:
			// constant callbacks from glut
			static void IdleCallback();
			static void DisplayCallback();
			static void ReshapeCallback(int width, int height);
			static void CloseCallback();
		};
	}
}