#include "FileReader.h"

#include "../Engine/Rendering/General/Vertex.h"

using namespace Reading;
using namespace Engine::Rendering;

bool Reading::ReadStaticMesh(const std::string& file, GLuint& vao, std::vector<GLuint>& vbos, unsigned int& vertexCount)
{
	// store data for each vertex
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// store indices of faces
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;

	unsigned int currentSmoothingGroup = 0;
	unsigned int currentFaceIndex = 0;
	// std::vector<std::pair< GROUP ID, std::vector< FACE INDICES >>>
	//std::map<unsigned int, std::vector<unsigned int>> smoothingGroups;

	// try to open file
	FILE* objectFile = fopen(("..\\OpenGLTesting\\Assets\\Models\\" + file).c_str(), "r");
	if (objectFile == NULL)
	{
		std::cout << "Cannot open file! \n";
		return false;
	}

	// read file
	unsigned int lineNumber = 0;
	while (true)
	{
		lineNumber++;

		char line[256]; // lines can only have 256 characters (stupid);
		int flag = fscanf(objectFile, "%s", line);
		if (flag == EOF)
		{
			break;
		}
		
		if (strcmp(line, "v") == 0) // line stores vertex information
		{
			glm::vec3 newVertex;
			fscanf(objectFile, "%f %f %f\n", &newVertex.x, &newVertex.y, &newVertex.z);
			vertices.push_back(newVertex/100.0f);
		}
		else if (strcmp(line, "vn") == 0) // line stores vertex normal information
		{
			glm::vec3 newNormal;
			fscanf(objectFile, "%f %f %f\n", &newNormal.x, &newNormal.y, &newNormal.z);
			normals.push_back(newNormal);
		}
		else if (strcmp(line, "vt") == 0) // line stores uv information
		{
			glm::vec2 newUV;
			float unusedZValue;
			fscanf(objectFile, "%f %f %f\n", &newUV.x, &newUV.y, &unusedZValue);
			uvs.push_back(newUV);
		}
		else if (strcmp(line, "s") == 0) // line stores smoothing information
		{
			fscanf(objectFile, "%i", &currentSmoothingGroup);
		}
		else if (strcmp(line, "f") == 0) // line stores face information
		{
			unsigned int newVertexIndices[3];
			unsigned int newNormalIndices[3];
			unsigned int newUVIndices[3];

			int matches = fscanf(objectFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&newVertexIndices[0], &newUVIndices[0], &newNormalIndices[0],
				&newVertexIndices[1], &newUVIndices[1], &newNormalIndices[1],
				&newVertexIndices[2], &newUVIndices[2], &newNormalIndices[2]);

			if (matches != 9)
			{
				std::cout << "File cannot be read by this parser, investigate on line: " << line << std::endl;
				return false;
			}

			vertexIndices.push_back(newVertexIndices[0]);
			uvIndices.push_back(newUVIndices[0]);
			normalIndices.push_back(newNormalIndices[0]);

			vertexIndices.push_back(newVertexIndices[1]);
			uvIndices.push_back(newUVIndices[1]);
			normalIndices.push_back(newNormalIndices[1]);

			vertexIndices.push_back(newVertexIndices[2]);
			uvIndices.push_back(newUVIndices[2]);
			normalIndices.push_back(newNormalIndices[2]);

			/*
			auto smoothingGroup = smoothingGroups.find(currentSmoothingGroup);
			if (smoothingGroup == smoothingGroups.end())
			{
				smoothingGroup[currentSmoothingGroup] = std::vector<unsigned int>(currentFaceIndex);
			}
			else
			{
				(smoothingGroup->second).push_back(currentFaceIndex);
			}
			*/
			currentFaceIndex++;
		}
	}
	// total number of vertices
	vertexCount = vertexIndices.size();

	/* 
	// Debugging
	std::cout << "vertex count: " << vertices.size() << std::endl;
	std::cout << "normal count: " << normals.size() << std::endl;
	std::cout << "uv count: " << uvs.size() << std::endl;
	*/

	// figure out what to do with smoohting info

	// create opengl object in given vao and vbos
	GLuint newVao;
	GLuint newVbo;

	glGenVertexArrays(1, &newVao);
	glBindVertexArray(newVao);

	std::vector<Vertex> objectVerticesInformation;
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		/*
		// Debugging
		std::cout << "Current Index: " << i << std::endl;
		std::cout << "Resulint in: vertex: " << vertexIndices[i] << ", normal: " << normalIndices[i] << ", uv: " << uvIndices[i] << std::endl;
		*/
		objectVerticesInformation.push_back(Vertex(vertices[vertexIndices[i] - 1], normals[normalIndices[i] - 1], uvs[uvIndices[i] - 1]));
	}

	glGenBuffers(1, &newVbo);
	glBindBuffer(GL_ARRAY_BUFFER, newVao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexIndices.size(), &objectVerticesInformation[0], GL_STATIC_DRAW);

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

	glBindVertexArray(0);

	vao = newVao;
	vbos.push_back(newVbo);

	return true;
}

bool Reading::ReadBMP(const std::string& file, GLuint& textureId)
{
	unsigned char header[54]; // bmp always has a 54 byte header
	unsigned int dataPos; // position in file where data actually starts
	unsigned int width;
	unsigned int height;
	unsigned int imageSize; // width * height * 3 (3 for rbg)

	unsigned char* data; // actual data

	FILE* bmpFile = fopen(("..\\OpenGLTesting\\Assets\\" + file).c_str(), "rb");

	if (!bmpFile)
	{
		std::cout << "Image could not be opened!" << std::endl;
		return false;
	}

	if (fread(header, 1, 54, bmpFile) != 54 || header[0] != 'B' || header[1] != 'M') // not 54 bytes, not starting with 'BM' -> issue
	{
		std::cout << "Not a correct BMP file!" << std::endl;
		return false;
	}

	dataPos = *(int*)&(header[0x0A]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	imageSize = *(int*)&(header[0x22]);

	// make up any missing information
	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}
	if (dataPos == 0)
	{
		dataPos = 54; // starts after header
	}

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, bmpFile);

	fclose(bmpFile);

	GLuint newTextureId;
	glGenTextures(1, &newTextureId);
	glBindTexture(GL_TEXTURE_2D, newTextureId); // bind texture that is to be used

	// if texture is of size NOT divisible by 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// set reading values
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data); // give image to OpenGL

	delete data;

	textureId = newTextureId;
	return true;
}
