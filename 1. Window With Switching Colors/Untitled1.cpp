#include "./../glad.c"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_inputs(GLFWwindow*window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
		
	else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		
	else if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		
	else if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

int main()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
	while(! glfwWindowShouldClose(window))
	{
		process_inputs(window);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
}
