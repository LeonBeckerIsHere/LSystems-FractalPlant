#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "LSystem.h"
#include "PointAngle.h"
#include "Shader.h"
#include "Render.h"

/*
void addToVertices();
GLfloat count = 0.5f;
bool flag = false;
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void centerWindow(GLFWwindow* window, int width, int height);
void initInput();

const GLuint WIDTH = 800, HEIGHT = 800;

int maxDepth;

GLfloat zComp = 0.0f;

std::vector<GLfloat> vertices = { 0.0f, 0.0f, zComp, 0.0f, 0.0f, zComp };

int main() 
{
	initInput();
	//Initialize GLFW
	glfwInit();

	//Set required glfw hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create GLFW window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Fractal Plant", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glewExperimental = GL_TRUE;

	glewInit();

	centerWindow(window, WIDTH, HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	Shader shader("vertex.glsl", "fragment.glsl");

	Render r(&vertices, zComp);

	LSystem lsysPlant("X", maxDepth, 0.88f, r);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (lsysPlant.getCurrentOrder() <= lsysPlant.getOrder())
		{
			lsysPlant.executeOrder();
		}

		//addToVertices();

		glClearColor(0.0f, 0.0f, 0.10f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.progUse();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINES, 0, vertices.size());
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	std::cout << "Number of vertices in vector<GLfloat> vertices: " << vertices.size()/3 << std::endl;
	//std::cout << "Next Order is: " << lsysPlant.getOrder() + 1 << std::endl;
	//std::cout << lsysPlant.getCurrentStringOrder();
	std::getchar();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void centerWindow(GLFWwindow* window, int width, int height)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
}

void initInput()
{
	std::cout << "Hello, welcome to FractalPlant by Leon Becker.\nPlease enter an integer for max depth of the plant (Rec. 6): ";
	std::cin >> maxDepth;
}


/*
void addToVertices()
{
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(zComp);
	if (flag)
		vertices.push_back(count);
	else
		vertices.push_back(-count);
	vertices.push_back(count);
	vertices.push_back(zComp);

	count += 0.1f;
	flag = !flag;
}
*/