#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
using namespace std;

void init(int W, int H);
void display(void);
void drawCube();

int main()
{
	const int W = 600;
	const int H = 480;
	if(glfwInit() == false)
	{
		//not supported
		fprintf(stderr, "GLFW failed to initialize");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(W, H, "GLFW Window", NULL, NULL);
	
	if(!window)
	{
		fprintf(stderr, "Could Not create window\n");
		glfwTerminate();
		return -1;
	}
	init(W, H);
	glfwMakeContextCurrent(window);
	display();
	while(!glfwWindowShouldClose(window)) // main loop for the window
    {
        glfwSwapBuffers(window);
        glfwWaitEvents();
        
    }
    glfwDestroyWindow(window); //Destroy the window and terminate the glfwInstance if the program exits the main loop
    glfwTerminate();	

	return 0;
}

void init(int W, int H)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 0.1f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1,0.1,0.1,1);
	glViewport(0, 0, W, H);
}

void display()
{
	drawCube();
}

void drawCube()
{
	glColor3f(1,1,1);
}