#include <cmath>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glwindow.h"
#include "mesh.h"
#include "shader.h"

std::vector<Mesh *> meshlist;
std::vector<Shader *> shaderlist;

// Window dimensions
const GLint WIDTH = 1600, HEIGHT = 900;
const float toRadians = 3.14159265f / 180.0f;

glWindow mainWindow;

float curAngle = 0.0f;

static const char *vShader1 = "Shaders/shader1.vert"; // Vertex Shader
static const char *fShader1 = "Shaders/shader1.frag"; // Fragment Shader

static const char *vShader2 = "Shaders/shader2.vert"; // Vertex Shader
static const char *fShader2 = "Shaders/shader2.frag"; // Fragment Shader

void CreateObject()
{

    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f, // 0. Back Left
        1.0f,  -1.0f, -1.0f, // 1. Back Right
        0.0f,  1.0f,  0.0f,  // 2. Top
        -1.0f, -1.0f, 1.0f,  // 3. Front Left
        1.0f,  -1.0f, 1.0f,  // 4. Front Right
        0.0f,  -2.0f, 0.0f   // 5. Bottom
    };

    GLuint indices[] = {
        3, 4, 2, 4, 3, 5, // draw front face
        0, 3, 2, 5, 3, 0, // draw left face
        1, 5, 0, 2, 1, 0, // draw back face
        4, 1, 2, 5, 1, 4  // draw right};
    };

    Mesh *obj1 = new Mesh;
    obj1->createMesh(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
    meshlist.push_back(obj1);

    Mesh *obj2 = new Mesh;
    obj2->createMesh(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
    meshlist.push_back(obj2);
}

void CreateShader()
{
    Shader *shader1 = new Shader;
    shader1->createFromFiles(vShader1, fShader1);
    shaderlist.push_back(shader1);

    Shader *shader2 = new Shader;
    shader2->createFromFiles(vShader2, fShader2);
    shaderlist.push_back(shader2);
}

int main()
{
    mainWindow = glWindow(WIDTH, HEIGHT);
    mainWindow.initialise();

    CreateObject();
    CreateShader();

    GLuint uniformProjection = 0, uniformModel = 0;
    glm::mat4 projection = glm::perspective(glm::radians(30.0f), GLfloat(WIDTH) / GLfloat(HEIGHT), 1.0f, 10.0f);

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        // Get + Handle user input events
        glfwPollEvents();

        curAngle += 0.01f;
        if (curAngle >= 360)
        {
            curAngle -= 360;
        }

        // Clear window
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //********************************************************

        shaderlist[0]->useShader();
        uniformModel = shaderlist[0]->getModelLocation();
        uniformProjection = shaderlist[0]->getProjectionLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.5f, -5.0f));
        model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
        model = glm::rotate(model, -curAngle * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshlist[0]->renderMesh();
        glUseProgram(0);

        //********************************************************

        shaderlist[1]->useShader();
        uniformModel = shaderlist[1]->getModelLocation();
        uniformProjection = shaderlist[1]->getProjectionLocation();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.5f, -5.0f));
        model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshlist[1]->renderMesh();
        glUseProgram(0);

        //********************************************************

        mainWindow.swapBuffers();
    }

    return 0;
}
