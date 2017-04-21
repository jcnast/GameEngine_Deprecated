#pragma once

#include "../General/RenderObject.h"

namespace Engine
{
	namespace Rendering
	{
		class Sprite : public RenderObject
		{
		public:
			Sprite(const std::string& textureFile, glm::vec3 topLeft = glm::vec3(-1.0, 0.0f, 1.0), glm::vec3 topRight = glm::vec3(1.0, 0.0f, 1.0), glm::vec3 bottomLeft = glm::vec3(-1.0, 0.0f, -1.0), glm::vec3 bottomRight = glm::vec3(1.0, 0.0f, -1.0));
			virtual ~Sprite();

			// initialization based
			virtual void Destroy() override;

			// consistently called
			virtual void Draw(const glm::mat4& matrix, const glm::vec4& color);
		};
	}
}