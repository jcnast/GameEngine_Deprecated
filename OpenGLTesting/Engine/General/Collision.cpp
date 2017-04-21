#include "Collision.h"

using namespace Engine;

// constructors
Collision::Collision(Colliders::Collider2D* const collider1, Colliders::Collider2D* const collider2, const glm::vec2& collisionPoint)
	: Collider1(collider1), Collider2(collider2), CollisionPoint(collisionPoint)
{
}

Collision::Collision(const Collision& collision)
	: Collider1(collision.Collider1), Collider2(collision.Collider2), CollisionPoint(collision.CollisionPoint)
{
}

void Collision::ApplyCollision() const
{
	Collider1->OnCollision(this);
	Collider2->OnCollision(this);
}

const Colliders::Collider2D*Collision::Collision::GetOtherCollider(const Colliders::Collider2D* collider) const
{
	if (collider == Collider1)
	{
		return Collider2;
	}

	if (collider == Collider2)
	{
		return Collider1;
	}

	return nullptr;
}

glm::vec2 Collision::GetCollisionPoint() const
{
	return CollisionPoint;
}