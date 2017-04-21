#pragma once

#include "Collider2D.h"

#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

#include "../General/Collision.h"
#include "../GameObjects/GameObject.h"

using namespace Engine;
using namespace GameObjects;
using namespace Colliders;

// constructors
Collider2D::Collider2D(GameObjects::GameObject* gameObject, float radius, bool trigger /*= false*/)
	: GameObject(gameObject), Radius(radius), Trigger(trigger)
{

}

Collider2D::~Collider2D()
{

}

void Collider2D::OnCollision(const Engine::Collision* collision)
{
	if (Trigger)
	{
		GameObject->OnTrigger(collision);
	}
	else
	{
		GameObject->OnCollision(collision);
	}
}

float Collider2D::GetRadius() const
{
	return Radius;
}

Engine::GameObjects::GameObject* Collider2D::GetGameObject() const
{
	return GameObject;
}

void Collider2D::SetGameObject(Engine::GameObjects::GameObject* newGameObject)
{
	GameObject = newGameObject;
}

bool Collider2D::InitialRangeCheck(const Colliders::Collider2D* collider) const
{
	float distance = glm::distance(GameObject->GetPosition(), collider->GetGameObject()->GetPosition());
	float touchDistance = Radius + collider->GetRadius();

	return distance <= touchDistance;
}