#pragma once

#include "GameObject.h"

#include "../General/Collision.h"
#include "../Colliders/Collider2D.h"
#include "../Rendering/General/RenderObject.h"

using namespace Engine;
using namespace GameObjects;
using namespace Colliders;

// constructors
GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float dt)
{

}

void GameObject::Render(const glm::mat4& matrix, const glm::vec4& color)
{
	OnRender();
	Draw(matrix, color);
}

void GameObject::OnCollision(const Collision* collision)
{
	// default is to move outside collided object
	const Collider2D* otherCollider = collision->GetOtherCollider(collider);

	glm::vec2 direction = collision->GetCollisionPoint() - otherCollider->GetGameObject()->GetPosition(); // direction from other collider to point of contact
	
	SetPosition(otherCollider->GetEdgeInDirection(direction) + direction * collider->GetRadius()); // move this object such that they no longer touch the shortest distance (from center to point of contact)
}

void GameObject::OnTrigger(const Collision* collision)
{
	// nothing happens on trigger by default
}

// miscellaneous methods
glm::vec2 GameObject::GetPosition()
{
	return glm::vec2(transform.Position.x, transform.Position.z);
}

void GameObject::SetPosition(const glm::vec2& newPosition)
{
	transform.Position.x = newPosition.x;
	transform.Position.z = newPosition.y;
}

void GameObject::SetScale(const float newScale)
{
	transform.Scale = newScale;
}

float GameObject::GetScale()
{
	return transform.Scale;
}

void GameObject::SetRotation(const glm::fquat& newRotation)
{
	transform.Rotation = newRotation;
}

glm::fquat GameObject::GetRotation()
{
	return transform.Rotation;
}

void GameObject::Draw(const glm::mat4& matrix, const glm::vec4& color)
{
	glm::mat4 transformedMatrix = matrix * transform.GetTransformationMatrix();

	renderObject->Draw(transformedMatrix, color);
}