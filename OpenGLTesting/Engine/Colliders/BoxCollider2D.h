#pragma once

#include "Collider2D.h"

#include "../../Dependencies/glm/glm.h"

namespace Engine
{
	namespace Colliders
	{
		class CircleCollider2D;

		class BoxCollider2D : public Collider2D
		{
			float Length; // along z (since y is up)
			float Width; // along x

		public:
			BoxCollider2D(Engine::GameObjects::GameObject* gameObject, float length, float width, bool trigger = false);
			virtual ~BoxCollider2D();

			virtual Engine::Collision* Intersects(Colliders::Collider2D* const collider);
			virtual Engine::Collision* Intersects(Colliders::CircleCollider2D* const collider);
			virtual Engine::Collision* Intersects(Colliders::BoxCollider2D* const collider);
			virtual bool Intersects(const Ray* line) const;
			virtual bool Intersects(const glm::vec2& point) const;

			virtual glm::vec2 GetEdgeInDirection(const glm::vec2& direction) const;

			const Ray* GetLeftEdge() const;
			const Ray* GetRightEdge() const;
			const Ray* GetTopEdge() const;
			const Ray* GetBottomEdge() const;
		};
	}
}
