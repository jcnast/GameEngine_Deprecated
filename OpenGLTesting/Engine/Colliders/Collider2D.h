#pragma once

#include "../../Dependencies/glm/glm.h"

namespace Engine
{
	class Collision;
	class Transform;
	class Ray;

	namespace GameObjects
	{
		class GameObject;
	}

	namespace Colliders
	{
		class BoxCollider2D;
		class CircleCollider2D;

		class Collider2D
		{
		protected:
			float Radius; // radius always exists, even for non-circles as a way to quickly cull possible collisions
			bool Trigger;

			Engine::GameObjects::GameObject* GameObject;

		public:
			Collider2D(Engine::GameObjects::GameObject* gameObject, float radius, bool trigger = false);
			virtual ~Collider2D();

			virtual void OnCollision(const Engine::Collision* collision);

			float GetRadius() const;

			/*
			NOTE: All of the below should return a GameSystem::Collision* that is then taken and handled

			IDEA: collision holds point of contact and the two objects that hit. OnCollision/OnTrigger is then called on both if they are colliders/triggers

			THOUGHT: Could we have multi threads that go through all objects to find collisions, then go through all collisions to notify the objects?
			*/
			virtual Engine::Collision* Intersects(Colliders::Collider2D* const collider) const = 0;
			virtual Engine::Collision* Intersects(Colliders::CircleCollider2D* const collider) const = 0;
			virtual Engine::Collision* Intersects(Colliders::BoxCollider2D* const collider) const = 0;
			// if true, call GetEdgeInDirection to find where (if needed - probably won't be in most cases)
			virtual bool Intersects(const Ray* line) const = 0;
			virtual bool Intersects(const glm::vec2& point) const = 0;

			Engine::GameObjects::GameObject* GetGameObject() const;
			void SetGameObject(Engine::GameObjects::GameObject* newGameObject);

			virtual glm::vec2 GetEdgeInDirection(const glm::vec2& direction) const = 0;

		protected:
			bool InitialRangeCheck(const Colliders::Collider2D* collider) const;
		};
	}
}