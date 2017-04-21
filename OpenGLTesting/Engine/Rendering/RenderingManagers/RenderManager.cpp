#include "RenderManager.h"

#include "../General/RenderObject.h"
#include "../Models/StaticModel.h"
#include "../General/Sprite.h"

using namespace Engine;
using namespace Engine::Rendering;
using namespace Engine::Rendering::RenderManagers;
using namespace Engine::Rendering::Models;

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
	for (auto object : WorldObjects)
	{
		delete object;
	}

	WorldObjects.clear();
}

void RenderManager::Draw(const glm::mat4& matrix, const glm::vec4& color)
{
	// draw static models
	for (auto object : WorldObjects)
	{
		object->Draw(matrix, color);
	}
	/*
	// draw animated models
	for (auto animatedModel : AnimatedModels)
	{
	animatedModel->Draw(matrix, color);
	}
	*/
}

void RenderManager::Update(unsigned int dt)
{
	for (auto object : WorldObjects)
	{
		//model->Update();
	}
}

const unsigned int RenderManager::AddStaticModel(GLuint program, const std::string& meshFile, const std::string& textureFile)
{
	StaticModel* newModel = new StaticModel(meshFile, textureFile);
	newModel->SetProgram(program);

	WorldObjects.push_back(newModel);

	return newModel->GetId();
}

const unsigned int RenderManager::AddSprite(GLuint program, const std::string& textureFile)
{
	Engine::Rendering::Sprite* newSprite = new Engine::Rendering::Sprite(textureFile);
	newSprite->SetProgram(program);

	WorldObjects.push_back(newSprite);

	return newSprite->GetId();
}

void RenderManager::DeleteModel(const unsigned int iD)
{
	for (unsigned int i = 0; i < WorldObjects.size(); i++)
	{
		if (WorldObjects[i]->GetId() == iD)
		{
			WorldObjects[i]->Destroy();
			WorldObjects.erase(WorldObjects.begin() + i);
		}
	}
}

const RenderObject* RenderManager::GetModel(const unsigned int iD) const
{
	for (unsigned int i = 0; i < WorldObjects.size(); i++)
	{
		if (WorldObjects[i]->GetId() == iD)
		{
			return WorldObjects[i];
		}
	}

	return nullptr;
}