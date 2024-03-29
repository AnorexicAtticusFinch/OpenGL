#include "./../shader.h"
#include "./../camera.h"

#include <iostream>
using namespace std;

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const char* WINDOW_TITLE = "OpenGL Window";

glm::vec3 camPos(0, 0, 3);
glm::vec3 camFront(0, 0, -1);
glm::vec3 worldUp(0, 1, 0);
Camera cam(camPos, camFront, worldUp);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void cursor_callback(GLFWwindow* window, double xPos, double yPos)
{
    cam.mouse_movement(xPos, yPos);
}

void keyboard_inputs(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.keyboard_input(FORWARD, deltaTime);
    
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.keyboard_input(BACKWARD, deltaTime);
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.keyboard_input(RIGHT, deltaTime);
    
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.keyboard_input(LEFT, deltaTime);
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
    glfwSetCursorPosCallback(window, cursor_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Error during GLAD initialization" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0x00);

    Shader cubeShader("./cubeVertexShader.vs", "./cubeFragmentShader.fs");
    Shader outlineShader("./cubeVertexShader.vs", "./outlineFragmentShader.fs");

    float vertices[] = 
    {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    //LIGHTING PROPERTIES
    unsigned int diffTex = get2DTexID("./container2.png");
    unsigned int specTex = get2DTexID("./container2_specular.png");
    Material cubeMat;
    cubeMat.diffuse = 0;
    cubeMat.specular = 1;
    cubeMat.shininess = 128;

    pointLight pLight[2];
    pLight[0].position = glm::vec3(1.2, 0.75, 2);
    pLight[0].ambient = glm::vec3(0.2, 0.2, 0.2);
    pLight[0].diffuse = glm::vec3(0, 0, 1.5);
    pLight[0].specular = glm::vec3(1.5, 1.5, 1.5);
    pLight[0].constant = 1;
    pLight[0].linear = 0.22;
    pLight[0].quadratic = 0.20;

    pLight[1].position = glm::vec3(-1.2, 0.75, -2);
    pLight[1].ambient = glm::vec3(0.2, 0.2, 0.2);
    pLight[1].diffuse = glm::vec3(1.5, 0, 0);
    pLight[1].specular = glm::vec3(1.5, 1.5, 1.5);
    pLight[1].constant = 1;
    pLight[1].linear = 0.22;
    pLight[1].quadratic = 0.20;

    dirLight dLight;
    dLight.direction = glm::vec3(-1, -0.25, -3);
    dLight.ambient = glm::vec3(0.1, 0.1, 0.1);
    dLight.diffuse = glm::vec3(1, 1, 1);
    dLight.specular = glm::vec3(1.5, 1.5, 1.5);

    spotLight sLight;
    sLight.position = glm::vec3(1.2, 0.75, 2);
    sLight.direction = glm::vec3(-1, -0.25, -3);
    sLight.ambient = glm::vec3(0.4, 0.4, 0.4);
    sLight.diffuse = glm::vec3(1, 1, 1);
    sLight.specular = glm::vec3(1.5, 1.5, 1.5);
    sLight.constant = 1;
    sLight.linear = 0.14;
    sLight.quadratic = 0.07;
    sLight.innerCutoff = cos(glm::radians(10.5f));
    sLight.outerCutoff = cos(glm::radians(22.5f));
    //

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 500.0f);
    glm::mat4 transform;

    glm::mat4 model(1.0f), outlineModel(1.0f);
    outlineModel = glm::scale(outlineModel, glm::vec3(1.03f));

    float time, deltaTime, lastTime = 0;

    while (! glfwWindowShouldClose(window))
    {
        glStencilMask(0xFF);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glStencilMask(0x00);

        time = glfwGetTime();
        deltaTime = time - lastTime;
        lastTime += deltaTime;

        keyboard_inputs(window, deltaTime);

        transform = projection * cam.getViewMatrix();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffTex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specTex);

        sLight.position = cam.getPos();
        sLight.direction = cam.getFront();

        cubeShader.use();
        cubeShader.setFMat4Uniform("transform", transform);
        cubeShader.setFMat4Uniform("model", model);
        cubeShader.setMaterialUniform("mat", cubeMat);
        cubeShader.setFVec3Uniform("camPos", cam.getPos());

        //LIGHTING PROPERTIES
        cubeShader.setDirLightMaterialUniform("dLights[0]", dLight);
        cubeShader.setIntUniform("numDirLights", 1);

        cubeShader.setPointLightMaterialUniform("pLights[0]", pLight[0]);
        cubeShader.setPointLightMaterialUniform("pLights[1]", pLight[1]);
        cubeShader.setIntUniform("numPointLights", 2);

        cubeShader.setSpotLightMaterialUniform("sLights[0]", sLight);
        cubeShader.setIntUniform("numSpotLights", 1);
        //

        glStencilMask(0xFF);
        
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glStencilMask(0x00);

        //OUTLINE
        transform = transform * outlineModel;
        outlineShader.use();
        cubeShader.setFMat4Uniform("transform", transform);
        cubeShader.setFMat4Uniform("model", outlineModel);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glEnable(GL_DEPTH_TEST);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        //

        glBindVertexArray(0);

        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}