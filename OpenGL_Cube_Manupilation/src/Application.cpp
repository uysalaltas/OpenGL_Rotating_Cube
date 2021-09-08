#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // Configuration and initialization of glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ------------------------------

    // Creating window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ------------------------------

    // glew initialization
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    // ------------------------------

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    // -----------------------------

    cout << glGetString(GL_VERSION) << endl;

    Shader ourShader(
        "C:\\Users\\uysal\\source\\repos\\OpenGL_Cube_Manupilation\\OpenGL_Cube_Manupilation\\src\\shader.vert",
        "C:\\Users\\uysal\\source\\repos\\OpenGL_Cube_Manupilation\\OpenGL_Cube_Manupilation\\src\\shader.frag"
    );  
    float vertices[] = {
        //
        -0.5f, -0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 0.0f,
        //        
        -0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 0.0f,
        //        
        -0.5f,  0.25f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.25f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.25f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.25f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.25f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.25f,  0.5f,  0.0f, 0.0f, 1.0f,
        //        
         0.5f,  0.25f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.25f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.25f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.25f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.25f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.25f,  0.5f,  1.0f, 1.0f, 0.0f,
         // TOP
        -0.5f, -0.25f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.25f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.25f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.25f, -0.5f,  0.0f, 1.0f, 1.0f,
        // BOTTOM 2
        -0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.25f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.25f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.25f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.25f, -0.5f,  1.0f, 0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // ------------------------------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::lookAt(glm::vec3(0.0f, 1.0f, -3.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("projection", projection);

        // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}