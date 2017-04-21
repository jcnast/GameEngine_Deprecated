#pragma once

#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/quaternion.hpp"

namespace Engine
{
	class Camera
	{
	private:
		const glm::vec3 DefaultDirection = glm::vec3(0.0f, 0.0f, -1.0f);

		glm::vec3 Position; // position of camera
		glm::vec3 Direction; // direction the camera is looking

		glm::fquat Rotation;
		glm::mat4 RotationMatrix;

		glm::mat4 ProjectionMatrix;

		float AspectRatio;
		float FOVY = glm::radians(45.0f);
		int Width;
		int Height;

		float NearPlane = 0.1f;
		float FarPlane = 100.0f;

	public:
		Camera(const int& width, const int& height, const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& direction = glm::vec3(0.0f, 0.0f, -1.0f));

		// additional functions
		glm::vec3 MouseToWorld(const glm::vec2& screenPosition);
		glm::vec2 WorldToMouse(const glm::vec3& worldPosition);

		// getters and setters
		glm::vec3 GetPosition();
		void SetPosition(const glm::vec3& newPosition);
		
		glm::vec3 GetDirection();
		void SetDirection(const glm::vec3& newDirection);
		
		glm::fquat GetRotation();
		void SetRotation(const glm::fquat& newRotation);
		
		void SetAspectRatio(const int& width, const int& height);
		void SetFOVY(const float newFOVY);

		float GetNear();
		void SetNear(const float newNearPlane);

		float GetFar();
		void SetFar(const float newFarPlane);

		glm::mat4 GetRenderMatrix();

	private:
		void RecalculateRotationMatrix();
		void RecalculateProjectionMatrix();
	};
}