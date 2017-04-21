#pragma once

#include "../General/RenderObject.h"

namespace Engine
{
	namespace Rendering
	{
		namespace Models
		{
			class StaticModel : public RenderObject
			{
			public:
				StaticModel(const std::string& meshFile, const std::string& textureFile);
				virtual ~StaticModel();

				// initialization based
				virtual void Destroy() override;

				// consistently called
				virtual void Draw(const glm::mat4& matrix, const glm::vec4& color);
			};
		}
	}
}