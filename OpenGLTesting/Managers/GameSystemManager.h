#pragma once

#include "../Engine/Colliders/Collider2D.h"

#include <vector>

namespace Managers
{
	class GameSystemManager
	{
	private:
		std::vector<Engine::Colliders::Collider2D*> Colliders;

	public:
		GameSystemManager();
		~GameSystemManager();

		void Update(unsigned int dt = 0);
	};
}