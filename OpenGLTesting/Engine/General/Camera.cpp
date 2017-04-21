#pragma once

#include "Camera.h"

#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/gtx/quaternion.hpp"

using namespace Engine;

Camera::Camera(const int& width, const int& height, const glm::vec3& position, const glm::vec3& direction)
{
	Position = position;
	Direction = glm::normalize(direction);

	SetAspectRatio(width, height);

	glm::quat newRotation = glm::rotation(DefaultDirection, Direction); // rotation takes normalized vectors
	SetRotation(newRotation);

	WorldToMouse(MouseToWorld(WorldToMouse(glm::vec3(-5.0f, 5.0f, 0.0f))));
}

glm::vec3 Camera::MouseToWorld(const glm::vec2& screenPosition)
{
	float worldX = screenPosition.x / Width * 2.0f - 1.0f;
	float worldY = 1.0f - screenPosition.y / Height * 2.0f;

	glm::mat4 inverseMVP = glm::inverse(GetRenderMatrix());

	glm::vec4 worldPosition = inverseMVP * glm::vec4(worldX, worldY, 0.0f, 1.0f);

	return glm::vec3(worldPosition.x, worldPosition.y, worldPosition.z) / worldPosition.w;
	/*
		This gives the world coordinate of clicked area. Using the vector of camera->this (given by: this - camera) you 
		can calculate the coordinates that would be found at y = 0.

		Note: Create a ray class that has a direction and origin and can test for intersection & find the values when an axis (typically y) is 0
	*/
}

glm::vec2 Camera::WorldToMouse(const glm::vec3& worldPosition)
{
	glm::mat4 MVP = GetRenderMatrix();
	glm::vec3 transformedPosition = MVP * glm::vec4(worldPosition, 1.0f);

	float screenX = transformedPosition.x / transformedPosition.z; // scaled down based on distance from 0 x
	float screenY = transformedPosition.y / transformedPosition.z; // scaled down based on distance from 0 y

	screenX = (screenX + 1.f) * 0.5f * Width;
	screenY = (1.0f - screenY) * 0.5f * Height; // y goes from top to bottom in screen space

	return glm::vec2(screenX, screenY);
}

// getters and setters
glm::vec3 Camera::GetPosition()
{
	return Position;
}

void Camera::SetPosition(const glm::vec3& newPosition)
{
	Position = newPosition;
}

glm::vec3 Camera::GetDirection()
{
	return Direction;
}

void Camera::SetDirection(const glm::vec3& newDirection)
{
	Direction = glm::normalize(newDirection);

	SetRotation(glm::rotation(DefaultDirection, Direction));
}

glm::fquat Camera::GetRotation()
{
	return Rotation;
}

void Camera::SetRotation(const glm::fquat& newRotation)
{
	Rotation = newRotation;

	RecalculateRotationMatrix();
}

void Camera::SetAspectRatio(const int& width, const int& height)
{
	Width = width;
	Height = height;

	AspectRatio = float(width)/float(height);

	RecalculateProjectionMatrix();
}

void Camera::SetFOVY(const float newFOVY)
{
	FOVY = newFOVY;

	RecalculateProjectionMatrix();
}

float Camera::GetNear()
{
	return NearPlane;
}

void Camera::SetNear(const float newNearPlane)
{
	NearPlane = newNearPlane;

	RecalculateProjectionMatrix();
}

float Camera::GetFar()
{
	return FarPlane;
}

void Camera::SetFar(const float newFarPlane)
{
	FarPlane = newFarPlane;

	RecalculateProjectionMatrix();
}

glm::mat4 Camera::GetRenderMatrix()
{
	// Reference: http://www.ntu.edu.sg/home/ehchua/programming/opengl/cg_basicstheory.html
	glm::mat4 transformationMatrix(1.0f);
	// set translation portion
	{
		transformationMatrix[3][0] = -Position.x;
		transformationMatrix[3][1] = -Position.y;
		transformationMatrix[3][2] = -Position.z;
	}
	transformationMatrix = RotationMatrix * transformationMatrix; // rotate it

	return ProjectionMatrix * transformationMatrix;
}

void Camera::RecalculateRotationMatrix()
{
	RotationMatrix = glm::toMat4(glm::conjugate(Rotation));
}

void Camera::RecalculateProjectionMatrix()
{
	ProjectionMatrix = glm::perspective(FOVY, AspectRatio, NearPlane, FarPlane);
}