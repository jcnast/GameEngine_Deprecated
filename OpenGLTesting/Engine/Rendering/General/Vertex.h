#pragma once

#include "../../Dependencies/glm/glm.hpp"

namespace Engine
{
	namespace Rendering
	{
		struct Vertex
		{
			glm::vec3 Position; // standard vertex attribute
			glm::vec3 Normal; // nvertex normal
			glm::vec2 UVPosition; // first additional vertex attribute

			Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uvPosition)
			{
				Position = pos;
				Normal = normal;
				UVPosition = uvPosition;
			}

			Vertex() {}
		};
	}
}