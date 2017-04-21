#pragma once

#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/quaternion.hpp"

namespace Engine
{
	class Transform
	{
	public:
		glm::vec3 Position;
		float Scale;
		glm::fquat Rotation;
		glm::vec4 Color;

	public:
		// constructors
		Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const float& scale = 1.0f, const glm::fquat& rotation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec4& color = glm::vec4(1.0f));
		Transform(const Transform& transform);

		glm::mat4 GetTransformationMatrix();
	};
}