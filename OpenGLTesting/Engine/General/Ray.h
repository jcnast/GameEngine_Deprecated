#pragma once

// represents a ray cast from one point in a direction (for a set distance if required) to be used for raycasting

#include "../../Dependencies/glm/glm.hpp"

namespace Engine
{
	class Ray
	{
		glm::vec3 StartPosition;
		glm::vec3 Direction;
		float Length = -1.0f; // length of <= 0.0f means unlimited

	public:
		// constructors
		Ray(const glm::vec3& startPosition, const glm::vec3& direction, const float& length = -1.0f);
		Ray(const Ray& ray);

		bool IsInfinte() const;

		glm::vec3 GetStartPosition() const;
		glm::vec2 GetStartPosition2D() const;

		glm::vec3 GetDirection() const;
		glm::vec2 GetDirection2D() const;

		float GetLength() const;

		bool Intersects(const Ray* line) const;

		float ShortestDistanceFromPoint(glm::vec3& point) const;
		float ShortestDistanceFromPoint2D(glm::vec2& point) const;
		glm::vec3 PointAtGivenX(float x) const;
		glm::vec3 PointAtGivenY(float y) const;
		glm::vec3 PointAtGivenZ(float z) const;
	};
}