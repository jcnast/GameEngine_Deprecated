#pragma once

// represents collision between two colliders (and their gameobjects)

#include "../Colliders/Collider2D.h"

#include "../../Dependencies/glm/glm.hpp"

namespace Engine
{
	class Collision
	{
		Colliders::Collider2D* const Collider1;
		Colliders::Collider2D* const Collider2;
		const glm::vec2 CollisionPoint;

		// for physics sim, could make this include speed of impact and such...

	public:
		// constructors
		Collision(Colliders::Collider2D* const collider1, Colliders::Collider2D* const collider2, const glm::vec2& collisionPoint);
		Collision(const Collision& collision);

		void ApplyCollision() const;
		const Colliders::Collider2D* GetOtherCollider(const Colliders::Collider2D* collider) const;

		glm::vec2 GetCollisionPoint() const;
	};
}