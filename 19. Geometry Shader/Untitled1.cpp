#include "./../shader.h"
#include "./../camera.h"

#include <iostream>
using namespace std;

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;
const char* WINDOW_TITLE = "OpenGL Window";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (glfwInit() == GLFW_FALSE)
    {
        cout << "Error during GLFW initialization" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == NULL)
    {
        cout << "Error during GLFW window creation" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if (! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Error during GLAD initialization" << endl;
        return -1;
    }

    Shader shaderProgram("vertexShader.vs", "geometryShader.gs", "fragmentShader.fs");

    float vertices[] = 
    {
        -0.4, -0.4,
         0.4, -0.4,
         0.4,  0.4,
        -0.4,  0.4
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (! glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 4);
        glBindVertexArray(0);

        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
