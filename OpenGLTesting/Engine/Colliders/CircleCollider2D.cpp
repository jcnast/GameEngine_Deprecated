#include "CircleCollider2D.h"

#include "BoxCollider2D.h"

#include "../General/Collision.h"
#include "../General/Ray.h"
#include "../GameObjects/GameObject.h"

#include "../../Dependencies/glm/gtx/projection.h"

using namespace Engine;
using namespace Colliders;

CircleCollider2D::CircleCollider2D(Engine::GameObjects::GameObject* gameObject, float radius, bool trigger /*= false*/)
	: Collider2D(gameObject, radius, trigger)
{

}

CircleCollider2D::~CircleCollider2D()
{

}

Collision* CircleCollider2D::Intersects(Colliders::Collider2D* const collider)
{
	return collider->Intersects(this);
}

Collision* CircleCollider2D::Intersects(Colliders::CircleCollider2D* const collider)
{
	if (InitialRangeCheck(collider))
	{
		glm::vec2 direction = collider->GetGameObject()->GetPosition() - GameObject->GetPosition();

		glm::vec2 thisEdge = GetEdgeInDirection(direction);
		glm::vec2 thatEdge = collider->GetEdgeInDirection(-direction);

		Collision* resultingCollision = new Collision(this, collider, (thisEdge + thatEdge) * 0.5f);
		return resultingCollision;
	}

	return nullptr;
}

Collision* CircleCollider2D::Intersects(Colliders::BoxCollider2D* const collider)
{
	if (InitialRangeCheck(collider))
	{
		// create ray for each side of the rectangle
		// check if any of the rays are in the circle, or if the center point is in the circle, or if the center point of circle is in rectangle
		bool circleInBox = collider->Intersects(GameObject->GetPosition());
		bool boxIncircle = Intersects(collider->GetGameObject()->GetPosition());

		bool leftEdgeCollides = Intersects(collider->GetLeftEdge());
		bool rightEdgeCollides = Intersects(collider->GetRightEdge());
		bool topEdgeCollides = Intersects(collider->GetTopEdge());
		bool bottomEdgeCollides = Intersects(collider->GetBottomEdge());

		if (circleInBox || boxIncircle || leftEdgeCollides || rightEdgeCollides || topEdgeCollides || bottomEdgeCollides)
		{
			glm::vec2 direction = collider->GetGameObject()->GetPosition() - GameObject->GetPosition();

			glm::vec2 thisEdge = GetEdgeInDirection(direction);
			glm::vec2 thatEdge = collider->GetEdgeInDirection(-direction);

			Collision* resultingCollision = new Collision(this, collider, (thisEdge + thatEdge) * 0.5f);
			return resultingCollision;
		}
	}

	return nullptr;
}

bool CircleCollider2D::Intersects(const Ray* line) const
{
	glm::vec2 startToCircle = GameObject->GetPosition() - line->GetStartPosition2D();
	float distance = glm::length(startToCircle);

	if (distance <= Radius)
	{
		// starts in range, so always in range
		return true;
	}

	if (!line->IsInfinte() /*|| (not going in x AND y direction towards object) */) // quick check
	{
		if (distance > line->GetLength() + Radius)
		{
			return false;
		}
	}

	if (line->ShortestDistanceFromPoint2D(GameObject->GetPosition()) <= Radius)
	{
		// passes through circle
		return true;
	}
	else
	{
		return false;
	}
}

bool CircleCollider2D::Intersects(const glm::vec2& point) const
{
	float distance = glm::distance(GameObject->GetPosition(), point);

	return distance <= Radius;
}

glm::vec2 CircleCollider2D::GetEdgeInDirection(const glm::vec2& direction) const
{
	if (direction.x == 0.0f && direction.y == 0.0f)
	{
		return GameObject->GetPosition();
	}

	glm::vec2 normalizedDirection = glm::normalize(direction);
	glm::vec2 edge = GameObject->GetPosition() + normalizedDirection * Radius;

	return edge;
}
