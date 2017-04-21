#pragma once

#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

namespace Engine
{
	namespace Rendering
	{
		namespace RenderManagers
		{
			class ShaderManager
			{
			public:
				ShaderManager();
				~ShaderManager();

				void CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilemame, const std::string& fragmentShaderFilename);

				static const GLuint GetShader(const std::string& shaderName);
				static void RemoveShader(const std::string& shaderName);

			private:
				std::string ReadShader(const std::string& filename);
				GLuint CreateShader(GLenum shaderType, const std::string source, const std::string& shaderName);

				static std::map<std::string, GLuint> Programs;
			};
		}
	}
}