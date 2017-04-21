#pragma once

#include "Collider2D.h"

#include "../GameObjects/GameObject.h"

#include "../../Dependencies/glm/glm.h"

namespace Engine
{
	namespace Colliders
	{
		class BoxCollider2D;

		class CircleCollider2D : public Collider2D
		{
		public:
			CircleCollider2D(Engine::GameObjects::GameObject* gameObject, float radius, bool trigger = false);
			virtual ~CircleCollider2D();

			virtual Engine::Collision* Intersects(Colliders::Collider2D* const collider);
			virtual Engine::Collision* Intersects(Colliders::CircleCollider2D* const collider);
			virtual Engine::Collision* Intersects(Colliders::BoxCollider2D* const collider);
			virtual bool Intersects(const Ray* line) const;
			virtual bool Intersects(const glm::vec2& point) const;

			virtual glm::vec2 GetEdgeInDirection(const glm::vec2& direction) const;
		};
	}
}