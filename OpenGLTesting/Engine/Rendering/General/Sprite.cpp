#include "Sprite.h"

#include "../../../Readers/FileReader.h"

#include <vector>

using namespace Engine::Rendering;
using namespace Reading;

Sprite::Sprite(const std::string& textureFile, glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft, glm::vec3 bottomRight)
{
	bool readTexture = ReadBMP(textureFile, Texture);

	assert(readTexture);

	//	since sprites are super basic rectangles, may as well set this up accordingly
	
	//triangle vertices on stack
	std::vector<Vertex> vertices;
	//specify vertex positions
	vertices.push_back(Vertex(bottomLeft, glm::vec3(0.0), glm::vec2(0.0f, 1.0f)));
	vertices.push_back(Vertex(topLeft, glm::vec3(0.0), glm::vec2(0.0f, 0.0f))); // top left is 0, 0
	vertices.push_back(Vertex(bottomRight, glm::vec3(0.0), glm::vec2(1.0f, 1.0f))); // bottom right is 1, 1
	vertices.push_back(Vertex(topRight, glm::vec3(0.0), glm::vec2(1.0f, 0.0f)));

	// create opengl object in given vao and vbos
	GLuint newVao;
	GLuint newVbo;

	glGenVertexArrays(1, &newVao);
	glBindVertexArray(newVao);

	glGenBuffers(1, &newVbo);
	glBindBuffer(GL_ARRAY_BUFFER, newVao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &vertices[0], GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::Normal)));
	//(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >)

	// texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::UVPosition)));

	Vao = newVao;
	Vbos.push_back(newVbo);
	VertexCount = 6;
}

Sprite::~Sprite()
{
	Destroy();
}

void Sprite::Destroy()
{
	glDeleteVertexArrays(1, &Vao);
	glDeleteBuffers(Vbos.size(), &Vbos[0]);
	Vbos.clear();
}

void Sprite::Draw(const glm::mat4& matrix, const glm::vec4& color)
{
	// overriden
	glUseProgram(Program);
	glBindVertexArray(Vao);

	// texture to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// calculate final matrix
	glm::mat4 transformationMatrix = matrix *  Pose.GetTransformationMatrix();
	glm::vec4 colorTransformation = glm::vec4(color[0] * Pose.Color[0], color[1] * Pose.Color[1], color[2] * Pose.Color[2], color[3] * Pose.Color[3]);

	// assign matrix to shader
	GLint MVP = glGetUniformLocation(Program, "MVP");
	glUniformMatrix4fv(MVP, 1, GL_FALSE, &transformationMatrix[0][0]);

	// assign color to shader
	GLint modColor = glGetUniformLocation(Program, "modColor");
	glUniform4fv(modColor, 1, &colorTransformation[0]);

	// assign texture to shader
	GLint texture = glGetUniformLocation(Program, "texture0");
	glUniform1i(texture, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
}