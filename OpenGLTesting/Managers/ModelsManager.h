#pragma once

#include "ShaderManager.h"

#include "../../Dependencies/glm/glm.hpp"

namespace Engine
{
	namespace Rendering
	{
		class RenderObject;
	}
}

namespace Managers
{
	class ModelsManager
	{
	private:
		std::vector<Engine::Rendering::RenderObject*> WorldObjects;
		// std::vector<RenderObject*> AnimatedModels;

	public:
		ModelsManager();
		~ModelsManager();

		void Draw(const glm::mat4& matrix, const glm::vec4& color);
		void Update(unsigned int dt = 0);

		const unsigned int AddStaticModel(GLuint program, const std::string& meshFile, const std::string& textureFile);
		const unsigned int AddSprite(GLuint program, const std::string& textureFile);
		// const unsigner int AddAnimatedModel(const std::string& file);
		void DeleteModel(const unsigned int iD);
		const Engine::Rendering::RenderObject* GetModel(const unsigned int iD) const;
	};
}