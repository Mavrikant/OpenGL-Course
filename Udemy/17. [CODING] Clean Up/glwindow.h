#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

class glWindow
{
  public:
    glWindow();
    glWindow(GLint windowWidth, GLint windowHeight);
    int initialise();
    GLint getBufferWidth() { return bufferWidth; }
    GLint getBufferHeight() { return bufferHeight; }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    ~glWindow();

  private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;
};

#endif // GLWINDOW_H
