#include "StaticModel.h"

#include "../../../Readers/FileReader.h"

using namespace Engine::Rendering;
using namespace Models;
using namespace Reading;

StaticModel::StaticModel(const std::string& meshFile, const std::string& textureFile)
{
	bool readMesh = ReadStaticMesh(meshFile, Vao, Vbos, VertexCount);
	bool readTexture = ReadBMP(textureFile, Texture);

	assert(readMesh && readTexture);
	

	//	BELOW IS FOR TESTING SINCE THE FILE READER IS BREAKING
	/*
	//triangle vertices on stack
	std::vector<Vertex> vertices;
	//specify vertex positions
	vertices.push_back(Vertex(glm::vec3(-1.0, 0.0f, 1.0), glm::vec3(0.0), glm::vec2(0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0), glm::vec2(0.0f, 0.0f)));
	vertices.push_back(Vertex(glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0), glm::vec2(0.0f, 0.0f)));

	// create opengl object in given vao and vbos
	GLuint newVao;
	GLuint newVbo;

	glGenVertexArrays(1, &newVao);
	glBindVertexArray(newVao);

	glGenBuffers(1, &newVbo);
	glBindBuffer(GL_ARRAY_BUFFER, newVao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &vertices[0], GL_STATIC_DRAW);

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
	VertexCount = 3;
	*/
}

StaticModel::~StaticModel()
{
	Destroy();
}

void StaticModel::Destroy()
{
	glDeleteVertexArrays(1, &Vao);
	glDeleteBuffers(Vbos.size(), &Vbos[0]);
	Vbos.clear();
}

void StaticModel::Draw(const glm::mat4& matrix, const glm::vec4& color)
{
	// shader and data to use
	glUseProgram(Program);
	glBindVertexArray(Vao);

	// texture to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// calculate final matrix
	glm::mat4 transformationMatrix = matrix * Pose.GetTransformationMatrix();
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

	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}