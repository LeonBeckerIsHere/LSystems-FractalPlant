#pragma once
#include <iostream>
#include <vector>
#include <GL\glew.h>
class Render {
private:
	std::vector<GLfloat> *vertices;
	GLfloat zComp;
public:
	Render() {}
	Render(std::vector<GLfloat> *v, GLfloat z);
	void draw(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void clearVertexVector();
	int size() { return vertices->size(); }
};
