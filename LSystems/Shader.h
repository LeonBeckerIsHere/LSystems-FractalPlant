#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
private:
	GLuint programID;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void progUse();

	GLuint getProgramId() { return programID; }
};