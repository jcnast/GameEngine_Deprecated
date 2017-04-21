#include "Ray.h"

using namespace Engine;

// constructors
Ray::Ray(const glm::vec3& startPosition, const glm::vec3& direction, const float& length)
	: StartPosition(startPosition), Direction(glm::normalize(direction)), Length(length)
{

}

Ray::Ray(const Ray& ray)
{
	StartPosition = ray.StartPosition;
	Direction = ray.Direction;
	Length = ray.Length;
}

bool Ray::IsInfinte() const
{
	return Length <= 0.0f;
}

glm::vec3 Ray::GetStartPosition() const
{
	return StartPosition;
}

glm::vec2 Ray::GetStartPosition2D() const
{
	return glm::vec2(StartPosition.x, StartPosition.z);
}

glm::vec3 Ray::GetDirection() const
{
	return Direction;
}

glm::vec2 Ray::GetDirection2D() const
{
	return glm::vec2(Direction.x, Direction.z);
}

float Ray::GetLength() const
{
	return Length;
}

bool Ray::Intersects(const Ray* line) const
{
	glm::vec3 tS = StartPosition;
	glm::vec3 tD = Direction;
	// this parametric equation: tF = tS + a * tD

	glm::vec3 oS = line->GetStartPosition();
	glm::vec3 oD = line->GetDirection();
	// other parametric equation = oF = oS + b * oD;

	if (tD.x == 0.0f || oD.z == 0.0f)
	{
		// TODO: DIVISION BY 0, DETERMINE HOW TO HANDLE
		return false;
	}

	// must use .x and .z since any 2D lines will have .y be 0 for everything
	float b = ((tS.z - oS.z + ((oS.x - tS.x) * tD.z / tD.x)) / oD.z) * ((tD.x * oD.z) / (tD.x * oD.z - oD.x * tD.z));
	float a = ((oS.x - tS.x) + (b * oD.x)) / tD.x;

	glm::vec3 tF = tS + a * tD;
	glm::vec3 oF = oS + b * oD;

	if (glm::distance(tF, oF) <= 0.0001f) // extended just to take floating point error into account
	{
		return true;
	}

	return false;
}

/* http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html */
float Ray::ShortestDistanceFromPoint(glm::vec3& point) const
{
	glm::vec3 StartToPoint = point - StartPosition;
	glm::vec3 StartToEnd = IsInfinte() ? glm::length(StartToPoint) * 2 * Direction : Length * Direction; // multiple StartToPoint length by 2 for safety
	glm::vec3 EndToPoint = point - (StartPosition + StartToEnd);

	float shortestDistance = glm::length(glm::cross(StartToPoint, EndToPoint)) / glm::length(StartToEnd);

	return shortestDistance; 
}

float Ray::ShortestDistanceFromPoint2D(glm::vec2& point) const
{
	return ShortestDistanceFromPoint(glm::vec3(point.x, 0.0f, point.y));
}

glm::vec3 Ray::PointAtGivenX(float x) const
{
	float a = (x - StartPosition.x) / Direction.x;

	return glm::vec3(StartPosition + a * Direction);
}

glm::vec3 Ray::PointAtGivenY(float y) const
{
	float a = (y - StartPosition.y) / Direction.y;

	return glm::vec3(StartPosition + a * Direction);
}

glm::vec3 Ray::PointAtGivenZ(float z) const
{
	float a = (z - StartPosition.z) / Direction.z;

	return glm::vec3(StartPosition + a * Direction);
}
