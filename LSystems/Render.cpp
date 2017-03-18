#include "Render.h"

Render::Render(std::vector<GLfloat> *v, GLfloat z)
{
	vertices = v;
	zComp = z;
}

void Render::draw(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) 
{ 
	//std::cout << "Drawing: " << x1 << y1 << x2 << y2;
	vertices->push_back(x1);
	vertices->push_back(y1);
	vertices->push_back(zComp);
	vertices->push_back(x2);
	vertices->push_back(y2);
	vertices->push_back(zComp);
};

void Render::clearVertexVector()
{
	vertices->clear();
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(zComp);
	vertices->push_back(0.0f);
	vertices->push_back(0.0f);
	vertices->push_back(zComp);
}