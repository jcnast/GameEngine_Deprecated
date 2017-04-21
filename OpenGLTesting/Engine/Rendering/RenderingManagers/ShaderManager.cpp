#include "ShaderManager.h"

using namespace Engine;
using namespace Engine::Rendering;
using namespace Engine::Rendering::RenderManagers;

std::map<std::string, GLuint> ShaderManager::Programs;

ShaderManager::ShaderManager()
{
	// nothing needs to be initialized
}
ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator index;
	for (index = Programs.begin(); index != Programs.end(); index++)
	{
		GLuint program = index->second;
		glDeleteProgram(program);
	}

	Programs.clear();
}

void ShaderManager::CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	// read the shader files and save the code
	std::string vertexShaderCode = ReadShader(vertexShaderFilename.c_str());
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename.c_str());

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader"); // create a vertex shader
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader"); // create a fragment shader

	int linkResult = 0;
	// create the program handle, attach the shader and link it
	GLuint program = glCreateProgram(); // creates empty program handle
	glAttachShader(program, vertexShader); // attach vertex shader to program
	glAttachShader(program, fragmentShader); // attach fragment shader to program
	glLinkProgram(program); // link the program
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult); // make sure program was linked properly

	// check for link errors
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "Shader Loader: LINK ERROR" << std::endl << &programLog[0] << std::endl;

		return;
	}

	std::map<std::string, GLuint>::iterator index;
	index = Programs.find(shaderName);
	if (index == Programs.end())
	{
		// add shader if name is not already used
		Programs[shaderName] = program;
	}
	else
	{
		std::cout << "ERROR shader <<" << shaderName.c_str() << ">> already exists!" << std::endl;
	}
}

const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	std::map<std::string, GLuint>::iterator index;
	index = Programs.find(shaderName);
	if (index != Programs.end())
	{
		// add shader if name is not already used
		return index->second;
	}
	else
	{
		// shader does not exist
		return 0;
	}
}

void ShaderManager::RemoveShader(const std::string& shaderName)
{
	std::map<std::string, GLuint>::iterator index;
	index = Programs.find(shaderName);
	if (index != Programs.end())
	{
		// add shader if name is not already used
		GLuint program = index->second;
		Programs.erase(index);
		glDeleteProgram(program);
	}
	
	return;
}

// essentially reading in a file
std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file: " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());

	file.close();
	return shaderCode;
}

// encapsulates all relevant operations to create a shader
GLuint ShaderManager::CreateShader(GLenum shaderType, const std::string source, const std::string& shaderName)
{
	int compileResult = 0;

	GLuint shader = glCreateShader(shaderType); // create shader creates an empty shader object (handle) of desired type
	const char* shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize); // loads the shader object with given code.
																// count is usually set to 1 because you normally have one character array
																// shaderCode is the array of code (array of size one in this case) and length is normally set to NULL (reads until NULL), but here we set it to the actual length
	glCompileShader(shader); // compiles the code
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult); // check for errors and output them to console
															  // the above set of operations is done for any shaders that we have to create their objects

															  // check for errors
	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shaderLog[0] << std::endl;

		return 0;
	}

	return shader;
}