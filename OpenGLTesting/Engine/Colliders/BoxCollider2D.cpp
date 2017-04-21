#include "BoxCollider2D.h"

#include "CircleCollider2D.h"

#include "../General/Collision.h"
#include "../General/Ray.h"
#include "../GameObjects/GameObject.h"

using namespace Engine;
using namespace Colliders;

BoxCollider2D::BoxCollider2D(GameObjects::GameObject* gameObject, float length, float width, bool trigger /*= false*/)
	: Collider2D(gameObject, sqrt(length*length + width*width), trigger), Length(length), Width(width)
{

}

BoxCollider2D::~BoxCollider2D()
{

}

Collision* BoxCollider2D::Intersects(Colliders::Collider2D* const collider)
{
	return collider->Intersects(this);
}

Collision* BoxCollider2D::Intersects(Colliders::CircleCollider2D* const collider)
{
	// no need to duplicate code, have circle check if these two collide
	return collider->Intersects(this);
}

Collision* BoxCollider2D::Intersects(Colliders::BoxCollider2D* const collider)
{
	// TODO: have this take rotation into account
	if (InitialRangeCheck(collider))
	{
		glm::vec2 thisPosition = GameObject->GetPosition();
		glm::vec2 thatPosition = collider->GetGameObject()->GetPosition();

		bool thisLeftThatRight = (thisPosition.x - Width * 0.5f) <= (thatPosition.x + collider->Width * 0.5f);
		bool thisRightThatLeft = (thisPosition.x + Width * 0.5f) >= (thatPosition.x - collider->Width * 0.5f);
		bool thisBottomThatTop = (thisPosition.x - Length * 0.5f) <= (thatPosition.x + collider->Length * 0.5f);
		bool thisTopThatBottom = (thisPosition.x + Length * 0.5f) >= (thatPosition.x - collider->Length * 0.5f);
		
		if (thisLeftThatRight && thisRightThatLeft && thisTopThatBottom && thisBottomThatTop)
		{
			glm::vec2 thisEdge = GetEdgeInDirection(thatPosition - thisPosition);
			glm::vec2 thatEdge = collider->GetEdgeInDirection(thisPosition - thatPosition);

			Collision* resultingCollistion = new Collision(this, collider, (thisEdge + thatEdge) * 0.5f);
			return resultingCollistion;
		}
	}

	return nullptr;
}

bool BoxCollider2D::Intersects(const Ray* line) const
{
	// TODO: have this take rotation into account (having GETEDGE take it into account should suffice)
	glm::vec2 startToBox = GameObject->GetPosition() - line->GetStartPosition2D();
	float distance = glm::length(startToBox);

	if (!line->IsInfinte() /*|| (not going in x AND y direction towards object)*/) // quick check
	{
		if (distance > line->GetLength() + Radius)
		{
			return false;
		}
	}

	bool startsInBox = Intersects(line->GetStartPosition2D());
	bool intersectsLeft = line->Intersects(GetLeftEdge());
	bool intersectsRight = line->Intersects(GetRightEdge());
	bool intersectsTop = line->Intersects(GetTopEdge());
	bool intersectsBottom = line->Intersects(GetBottomEdge());

	if (startsInBox || intersectsLeft || intersectsRight || intersectsTop || intersectsBottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoxCollider2D::Intersects(const glm::vec2& point) const
{
	// TODO: have this take rotation into account
	glm::vec2 thisPosition = GameObject->GetPosition();

	bool inFromRight = (thisPosition.x - Width * 0.5f) <= (point.x);
	bool inFromLeft = (thisPosition.x + Width * 0.5f) >= (point.x);
	bool inFromBottom = (thisPosition.y - Length * 0.5f) <= (point.y);
	bool inFromTop = (thisPosition.y + Length * 0.5f) >= (point.y);

	return (inFromRight && inFromLeft && inFromBottom && inFromTop);
}

glm::vec2 BoxCollider2D::GetEdgeInDirection(const glm::vec2& direction) const
{
	if (direction.x == 0.0f && direction.y == 0.0f)
	{
		return GameObject->GetPosition();
	}

	glm::vec2 position = GameObject->GetPosition();
	glm::vec2 edge;

	// TODO: have this take rotation into account
	if (direction.x*direction.x >= direction.y*direction.y) // direction is mostly along x
	{
		if (direction.x >= 0.0f)
		{
			edge = glm::vec2(position.x + Width * 0.5f, position.y);
		}
		else
		{
			edge = glm::vec2(position.x - Width * 0.5f, position.y);
		}
	}
	else
	{
		if (direction.y >= 0.0f)
		{
			edge = glm::vec2(position.x, position.y + Length * 0.5f);
		}
		else
		{
			edge = glm::vec2(position.x, position.y - Length * 0.5f);
		}
	}

	return edge;
}

const Ray* BoxCollider2D::GetLeftEdge() const
{
	// TODO: have this take rotation into account
	glm::vec2 position = GameObject->GetPosition();

	glm::vec3 startPosition = glm::vec3(position.x - Width * 0.5f, 0.0f, position.y - Length * 0.5f); // bottom left
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f); // going up

	Ray* leftEdge = new Ray(startPosition, direction, Length);
	return leftEdge;
}

const Ray* BoxCollider2D::GetRightEdge() const
{
	// TODO: have this take rotation into account
	glm::vec2 position = GameObject->GetPosition();

	glm::vec3 startPosition = glm::vec3(position.x + Width * 0.5f, 0.0f, position.y - Length * 0.5f); // bottom right
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f); // going up

	Ray* rightEdge = new Ray(startPosition, direction, Length);
	return rightEdge;
}

const Ray* BoxCollider2D::GetTopEdge() const
{
	// TODO: have this take rotation into account
	glm::vec2 position = GameObject->GetPosition();

	glm::vec3 startPosition = glm::vec3(position.x - Width * 0.5f, 0.0f, position.y + Length * 0.5f); // top left
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f); // going right

	Ray* topEdge = new Ray(startPosition, direction, Width);
	return topEdge;
}

const Ray* BoxCollider2D::GetBottomEdge() const
{
	// TODO: have this take rotation into account
	glm::vec2 position = GameObject->GetPosition();

	glm::vec3 startPosition = glm::vec3(position.x - Width * 0.5f, 0.0f, position.y - Length * 0.5f); // bottom left
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f); // going right

	Ray* bottomEdge = new Ray(startPosition, direction, Width);
	return bottomEdge;
}