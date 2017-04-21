#pragma once

#include "Transform.h"

#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/gtx/quaternion.hpp"

using namespace Engine;

// constructors
Transform::Transform(const glm::vec3& position, const float& scale, const glm::fquat& rotation, const glm::vec4& color)
{
	Position = position;
	Scale = scale;
	Rotation = rotation;
	Color = color;
}

Transform::Transform(const Transform& transform)
{
	Position = transform.Position;
	Scale = transform.Scale;
	Rotation = transform.Rotation;
}

glm::mat4 Transform::GetTransformationMatrix()
{
	glm::mat4 transformationMatrix(Scale); // identity matrix that sets scale
	transformationMatrix[3][3] = 1.0f; // last of the diagonal needs to be one
	// opposite of camera since we want to rotate the object and then move it, where camera is inverting this operation (moving it by opposite, then rotating the movement)
	transformationMatrix = glm::toMat4(glm::conjugate(Rotation)) * transformationMatrix; // rotate it
	// set translation portion
	{
		transformationMatrix[3][0] = Position.x;
		transformationMatrix[3][1] = Position.y;
		transformationMatrix[3][2] = Position.z;
	}

	return transformationMatrix;
}