#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include "../Dependencies/glm/glm.hpp"

#include "../Engine/Rendering/Models/StaticModel.h"

#include <vector>
#include <map>
#include <iostream>

//using namespace Rendering;

namespace Reading
{
	// reads model from file, assigns data buffers to vao and vbo, tells vertex count how many vertices to draw
	// NEED TO ALSO READ IN IMAGE DATA TO CREATE BUFFER TO READ FROM
	bool ReadStaticMesh(const std::string& file, GLuint& vao, std::vector<GLuint>& vbos, unsigned int& vertexCount);

	bool ReadBMP(const std::string& file, GLuint& textureId);
}