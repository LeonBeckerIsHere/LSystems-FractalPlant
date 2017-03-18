#include "LSystem.h"

LSystem::LSystem(std::string in, int o, float dist, Render &r) {
	order = o;
	distance = dist;
	currentOrder = in;
	nextOrder = "";
	PointAngle roo(-1.0f, -1.0f, 60.0f);
	root = roo;
	current = roo;
	n = 1;
	render = r;
}

void LSystem::executeOrder() 
{
	//std::cout << "Current Point and Angle: (" << current.x << ", " << current.y << ") " << current.angle << " degrees." << std::endl;

	if (n <= order)
	{ 
		if (currentOrder.empty())
		{
			std::cout << "Number of vertices in this fractal: " << render.size() / 3 << std::endl;

			if(n == order)
				std::cout << n << " Order/Depth Done! Max order/depth has been achieved." << std::endl;
			else
				std::cout << n << " Order/Depth Done! Press enter to continue to next order." << std::endl;

			std::getchar();
			currentOrder = nextOrder;
			nextOrder = "";
			std::stack<PointAngle> newStack;
			savePoints = newStack;
			current = root;
			if(n<order)
				render.clearVertexVector();
			n++;
		}
		else
		{
			switch (currentOrder.front())
			{
				case 'X':
					nextOrder += "F-[[X]+X]+F[+FX]-X";
					currentOrder.erase(currentOrder.begin());
					break;

				case 'F':
					nextOrder += "FF";
					x2 = current.x + (distance/pow(2,n-1))*cos(PI*current.angle/180.0f);
					y2 = current.y + (distance/pow(2,n-1))*sin(PI*current.angle/ 180.0f);
					
					render.draw(current.x, current.y, x2, y2);

					current.x = x2;
					current.y = y2;

					currentOrder.erase(currentOrder.begin());
					break;

				case '+':
					nextOrder += "+";
					current.angle -= 25.0f;
					currentOrder.erase(currentOrder.begin());
					break;

				case '-':
					nextOrder += "-";
					current.angle += 25.0f;
					currentOrder.erase(currentOrder.begin());
					break;

				case '[':
					//std::cout << "^^^^^SAVED^^^^^\n";
					nextOrder += "[";
					savePoints.push(current);
					currentOrder.erase(currentOrder.begin());
					break;

				case ']':
					//std::cout << "vvvvvRESTOREDvvvvv\n";
					nextOrder += "]";
					current = savePoints.top();
					savePoints.pop();
					currentOrder.erase(currentOrder.begin());
					break;

				default: std::cout << "error has occured";
					break;
			}
		}
	}
	//std::cout << "Order: " << n << std::endl;
	//std::cout << currentOrder;

}