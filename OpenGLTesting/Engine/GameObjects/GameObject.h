#pragma once

#include "../General/Transform.h"
#include "../Rendering/General/RenderObject.h"

namespace Engine
{
	class Collision;

	namespace Colliders
	{
		class Collider2D;
	}

	namespace GameObjects
	{
		class GameObject
		{
			Engine::Rendering::RenderObject* renderObject;
			Engine::Colliders::Collider2D* collider;

			Engine::Transform transform;

		public:
			GameObject();
			// object should never delete themselves.
			/*
				PLAN: GameObjectManager has several threads:
				Collision check threads: Goes through the game object groups (team1, team2, spells) to find collisions
				Collision handling threads: Goes through the collisions to apply them to objects

				Anything that results in a destruction of an object queues it up in the GameObjectManager (to not worry about future collisions in this loop)
				and the manager will delete them all at the end of frame loop
			*/
			virtual ~GameObject();

			virtual void Update(float dt = 0.0f);
			void Render(const glm::mat4& matrix, const glm::vec4& color);
			virtual void OnCollision(const Engine::Collision* collision);
			virtual void OnTrigger(const Engine::Collision* collision);

			// miscellaneous methods
			glm::vec2 GetPosition();
			void SetPosition(const glm::vec2& newPosition);

			void SetScale(const float newScale);
			float GetScale();

			void SetRotation(const glm::fquat& newRotation);
			glm::fquat GetRotation();

		protected:
			virtual void OnRender() = 0;

		private:
			void Draw(const glm::mat4& matrix, const glm::vec4& color);
		};
	}
}