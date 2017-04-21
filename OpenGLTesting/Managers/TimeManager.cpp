#include "TimeManager.h"

using namespace Managers;

TimeManager::TimeManager()
{
	StartTime = clock();
	LastTimeStep = StartTime;

	TimeModifier = 1.0f;
}

TimeManager::~TimeManager()
{
	
}

float TimeManager::GetDeltaTime()
{
	clock_t CurrentTimeStep = clock();

	float DeltaTime = float(CurrentTimeStep - LastTimeStep) / CLOCKS_PER_SEC;

	LastTimeStep = CurrentTimeStep;
	return (TimeModifier * DeltaTime);
}

void TimeManager::SetTimeModifier(float newTimeModifier)
{
	TimeModifier = newTimeModifier;
}

void TimeManager::ResetModifiers()
{
	TimeModifier = 1.0f;
}