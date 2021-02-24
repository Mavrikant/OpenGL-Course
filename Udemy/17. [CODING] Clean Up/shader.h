#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
  public:
    Shader();
    ~Shader();

    void createFromString(const char *vertexCode, const char *fragmentCode);
    void createFromFiles(const char *vertexLocation, const char *fragmentLocation);
    GLuint getProjectionLocation();
    GLuint getModelLocation();

    void useShader();
    void clearShader();

  private:
    GLuint sharerID, uniformProjection, uniformModel;
    std::string readFile(const char *fileLocation);
    void compileShader(const char *vertexCode, const char *fragmentCode);
    void addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
};

#endif // SHADER_H
