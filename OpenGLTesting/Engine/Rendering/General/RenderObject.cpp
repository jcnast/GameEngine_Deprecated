#include "RenderObject.h"

using namespace Engine::Rendering;

unsigned int RenderObject::NextId = 0;

RenderObject::RenderObject()
: iD(RenderObject::NextId++)
{
}

RenderObject::~RenderObject()
{
	// nothing
}


void RenderObject::SetProgram(GLuint program)
{
	Program = program;
}

const unsigned int RenderObject::GetId()
{
	return iD;
}

// setters and getters
void RenderObject::SetPosition(const glm::vec3& newPosition)
{
	Pose.Position = newPosition;
}

glm::vec3 RenderObject::GetPosition()
{
	return Pose.Position;
}

void RenderObject::SetScale(const float newScale)
{
	Pose.Scale = newScale;
}

float RenderObject::GetScale()
{
	return Pose.Scale;
}

void RenderObject::SetRotation(const glm::fquat& newRotation)
{
	Pose.Rotation = newRotation;
}

glm::fquat RenderObject::GetRotation()
{
	return Pose.Rotation;
}

// other methods
void RenderObject::Reset()
{
	Pose.Position = glm::vec3(0.0f);
	Pose.Scale = 1.0f;
	Pose.Rotation = glm::fquat(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderObject::MoveBy(const glm::vec3& movement)
{
	Pose.Position += movement;
}

void RenderObject::ScaleBy(const float scale)
{
	Pose.Scale *= scale;
}

void RenderObject::RotateBy(const glm::fquat& rotation)
{
	Pose.Rotation *= rotation;
}

GLuint const RenderObject::GetVao() const
{
	return Vao;
}

const std::vector<GLuint>& RenderObject::GetVbos() const
{
	return Vbos;
}

GLuint const RenderObject::GetTexture() const
{
	return Texture;
}