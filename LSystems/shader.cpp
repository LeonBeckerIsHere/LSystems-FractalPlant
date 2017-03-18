#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

	//recieve fragment and vertex source code
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	//Ensure files can throw exceptions
	vertexFile.exceptions(std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::badbit);

	try 
	{
		//open files
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream, fragmentStream;

		//read file contents into stream
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		//close files
		vertexFile.close();
		fragmentFile.close();

		//convert streams into strings and then into GLchar arrays
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR_SHADER_FILES_COULD_NOT_BE_READ" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infolog[512];

	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//Vertex shader error checking
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		std::cout << "ERROR_VERTEX_SHADER_COULD_NOT_BE_COMPILED\n" << infolog << std::endl;
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//fragment shader error checking
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infolog);
		std::cout << "ERROR_FRAGMENT_SHADER_COULD_NOT_BE_COMPILED\n" << infolog << std::endl;
	}

	//shader program
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex);
	glAttachShader(this->programID, fragment);
	glLinkProgram(this->programID);

	//program linking error checking
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->programID, 512, NULL, infolog);
		std::cout << "ERROR_PROGRAM_COULD_NOT_LINK_WITH_SHADERS\n" << infolog << std::endl;
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::progUse() {
	glUseProgram(this->programID);
}