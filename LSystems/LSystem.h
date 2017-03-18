#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "PointAngle.h"
#include "Render.h"

class LSystem {
private:
	int n;				//n is current order
	int order;
	float distance;
	float x2, y2;		//Next point
	std::string currentOrder;
	std::string nextOrder;
	PointAngle current;
	PointAngle root;
	std::stack<PointAngle> savePoints;
	Render render;
	const float PI = 3.14159265359f;

public:
	LSystem(std::string in, int o, float dist, Render &r);
	void executeOrder();
	int getOrder() { return order; }
	int getCurrentOrder() { return n; }
	float getDistance() { return distance; }
	std::string getCurrentStringOrder() { return currentOrder; }
	std::string getNextStringOrder() { return nextOrder; }
	void setOrder(int o) { order = o; }
	void setDistance(float d) { distance = d; }
};