#include "InitGlew.h"

using namespace Core;
using namespace Core::Init;

void InitGlew::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "Glew: Initialized" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << "GLEW GL_VERSION_4_5 IS supported" << std::endl;
	}
	else
	{
		std::cout << "GLEW GL_VERSION_4_5 is NOT supported" << std::endl;
	}
}