#include "InitGlut.h"

#include <iostream>

using namespace Core::Init;

Managers::ProgramManager* InitGlut::ProgramManager = NULL;
Core::WindowInfo InitGlut::WindowInfo;
//RECT InitGlut::WindowRect;
HWND InitGlut::ActiveWindow;
bool InitGlut::Running = true;

void InitGlut::Init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FrameBufferInfo& frameBufferInfo)
{
	// need to create these fake arguments since glutInit requires them
	int fakeArgc = 1;
	char *fakeArgv[] = {"Fake", NULL};
	glutInit(&fakeArgc, fakeArgv); // initialize glut

	// set window info variable
	WindowInfo = windowInfo;

	if (contextInfo.Core)
	{
		// in Core mode, we are hard setting the version of OpenGL we are going to use
		glutInitContextVersion(contextInfo.MajorVersion, contextInfo.MinorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		// if we are in compatability mode, then the version does not matter (since we are just using what we can)
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	// initialize window
	glutInitDisplayMode(frameBufferInfo.Flags); // use the flags that were set in the desired frame buffer info
	glutInitWindowPosition(windowInfo.PositionX, windowInfo.PositionY);
	glutInitWindowSize(windowInfo.Width, windowInfo.Height);
	// this must be called AFTER the above 3 methods, or they will have no effect
	glutCreateWindow(windowInfo.Name.c_str());

	std::cout << "GLUT: Initialized" << std::endl;

	// set glut callbacks
	glutIdleFunc(IdleCallback); // called when events are not being received
	glutCloseFunc(CloseCallback); // when window is closed
	glutDisplayFunc(DisplayCallback); // when visuals are displayed
	glutReshapeFunc(ReshapeCallback); // when window is reshaped

	// set windows callbacks
	//DefWindowProc(WindowProcedure);

	// initialize glew
	Init::InitGlew::Init();

	// cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// display some info (needs window and context info)
	PrintOpenGLInfo(windowInfo, contextInfo);

	// get active window
	int len;
	int slength = (int)WindowInfo.Name.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, WindowInfo.Name.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, WindowInfo.Name.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;

	ActiveWindow = FindWindow(NULL, r.c_str());
}

void InitGlut::Run()
{
	std::cout << "GLUT: Start Running" << std::endl;
	
	while (Running)
	{
		// ALWAYS do this instead of 'gluMainLoop()' as it allows you to set your OWN time for things
		glutMainLoopEvent(); // get any events from OS
		ProgramManager->NotifyUpdate(); // update game logic
		// could NOT have a display callback listener and call it yourself, but it would be heavier so for now let
		// glut determine when the display should get updated
		// if you did this yourself you could set your own framerate and such
	}
}

void InitGlut::Close()
{
	std::cout << "GLUT: Stop Running" << std::endl;
	glutLeaveMainLoop();
	Running = false;
}

void InitGlut::IdleCallback()
{
	// do nothing but redisplay
	glutPostRedisplay();
}

void InitGlut::DisplayCallback()
{
	if (ProgramManager)
	{
		ProgramManager->NotifyRender();
	}
}

void InitGlut::ReshapeCallback(int width, int height)
{
	if (WindowInfo.Reshapable)
	{
		if (ProgramManager)
		{
			ProgramManager->NotifyReshape(width, height, WindowInfo.Width, WindowInfo.Height);
		}

		WindowInfo.Width = width;
		WindowInfo.Height = height;
	}
}

void InitGlut::CloseCallback()
{
	Close();
}

void InitGlut::EnterFullscreen()
{
	glutFullScreen();
}

void InitGlut::ExitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGlut::SetProgramManager(Managers::ProgramManager*& programManager)
{
	ProgramManager = programManager;
	ProgramManager->NotifyReshape(WindowInfo.Width, WindowInfo.Height, WindowInfo.Width, WindowInfo.Height); // (currentWidth, currentHeight, previoudWidth, previousHeight);
}

void InitGlut::PrintOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "*****************************************" << std::endl;
	std::cout << "GLUT INFORMATION" << std::endl;
	std::cout << "GLUT Renderer: " << renderer << std::endl;
	std::cout << "GLUT VENDOR: " << vendor << std::endl;
	std::cout << "GLUT VERSION: " << version << std::endl;
}