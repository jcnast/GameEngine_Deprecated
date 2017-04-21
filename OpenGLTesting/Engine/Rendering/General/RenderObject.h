#pragma once

#include "Vertex.h"
#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"
#include "../../General/Transform.h"

#include <vector>
#include <iostream>

namespace Engine
{
	namespace Rendering
	{
		class RenderObject
		{
		protected:
			static unsigned int NextId;

			const unsigned int iD;

			GLuint Program;
			GLuint Vao;
			std::vector<GLuint> Vbos;
			GLuint Texture;
			unsigned int VertexCount = 0;

			Transform Pose;

		public:
			RenderObject();
			virtual ~RenderObject() = 0;

			virtual void Draw(const glm::mat4& matrix, const glm::vec4& color) = 0;
			virtual void Destroy() = 0;

			void SetProgram(GLuint program);

			const unsigned int GetId();

			// getters and setters
			void SetPosition(const glm::vec3& newPosition);
			glm::vec3 GetPosition();

			void SetScale(const float newScale);
			float GetScale();

			void SetRotation(const glm::fquat& newRotation);
			glm::fquat GetRotation();

			// other methods
			void Reset();

			void MoveBy(const glm::vec3& movement);
			void ScaleBy(float scale);
			void RotateBy(const glm::fquat& rotation);

			virtual const GLuint GetVao() const;
			virtual const std::vector<GLuint>& GetVbos() const;
			virtual const GLuint GetTexture() const;
		};
	}
}