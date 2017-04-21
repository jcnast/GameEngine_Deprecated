#pragma once

#include "Core/Init/InitGlut.h"
#include "Managers/ProgramManager.h"

using namespace Core;
using namespace Init;

int main(int argc, char **argv)
{
// Create general info for the current program
	WindowInfo window(std::string("Basic Game Engine"),
		800, 600, // size
		200, 200, // position
		true); // allow reshaping
	ContextInfo context(4, 5, true);
	FrameBufferInfo frameBuffer(true, true, true, true);

// Initialize the required pieces of information
	InitGlut::Init(window, context, frameBuffer);

	Managers::ProgramManager* Program = Managers::ProgramManager::GetInstance();
	Init::InitGlut::SetProgramManager(Program);

// Run the actual game
	InitGlut::Run();

	return 0;
}