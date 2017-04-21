#include "ModelsManager.h"

#include "../Engine/Rendering/General/RenderObject.h"
#include "../Engine/Rendering/Models/StaticModel.h"
#include "../Engine/Rendering/General/Sprite.h"

using namespace Managers;
using namespace Engine::Rendering;
using namespace Engine::Rendering::Models;

ModelsManager::ModelsManager()
{
}

ModelsManager::~ModelsManager()
{
	for (auto object : WorldObjects)
	{
		delete object;
	}

	WorldObjects.clear();
}

void ModelsManager::Draw(const glm::mat4& matrix, const glm::vec4& color)
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

void ModelsManager::Update(unsigned int dt)
{
	for (auto object : WorldObjects)
	{
		//model->Update();
	}
}

const unsigned int ModelsManager::AddStaticModel(GLuint program, const std::string& meshFile, const std::string& textureFile)
{
	StaticModel* newModel = new StaticModel(meshFile, textureFile);
	newModel->SetProgram(program);

	WorldObjects.push_back(newModel);

	return newModel->GetId();
}

const unsigned int ModelsManager::AddSprite(GLuint program, const std::string& textureFile)
{
	Engine::Rendering::Sprite* newSprite = new Engine::Rendering::Sprite(textureFile);
	newSprite->SetProgram(program);

	WorldObjects.push_back(newSprite);

	return newSprite->GetId();
}

void ModelsManager::DeleteModel(const unsigned int iD)
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

const RenderObject* ModelsManager::GetModel(const unsigned int iD) const
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