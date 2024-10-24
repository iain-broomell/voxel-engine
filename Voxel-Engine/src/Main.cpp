/*
Script inspired by OpenGL Course by Victor Gordan at FreeCodeCamp.org: https://www.youtube.com/watch?v=45MIykWJ-C4&t=2037s
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include"shaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Set version major/minor and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // triangle vertices which create an equalateral triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left corner
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right corner
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner bottom corner
    };

    GLuint indices[] = {
        0, 3, 5, // lower left triangle
        3, 2, 4, // lower right triangle
        5, 4, 1 // upper triangle
    };

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Renderer", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    // Generate a shader program using default shaders
    Shader shaderProgram("default.vert", "default.frag");

    // Create Vertex Array Object and set as current
    VAO VAO1;
    VAO1.Bind();

    // Generate buffer objects and pass in vertices and indices for setup
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Link Vertex Buffer Object to VAO, unbind buffers and arrays
    VAO1.LinkVBO(VBO1, 0);
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}