#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"

#include <time.h>

namespace Managers
{
	class TimeManager
	{
		clock_t StartTime;
		clock_t LastTimeStep;

		float TimeModifier;

	public:
		TimeManager();
		~TimeManager();

		float GetDeltaTime();

		void SetTimeModifier(float newTimeModifier);
		void ResetModifiers();
	};
}