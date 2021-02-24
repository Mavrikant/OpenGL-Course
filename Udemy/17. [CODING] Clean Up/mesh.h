#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>

class Mesh
{
  public:
    Mesh();
    ~Mesh();
    void createMesh(GLfloat *vertices, GLuint *indices, GLuint numOfVertices, GLuint numOfIndices);
    void renderMesh();
    void clearMesh();

  private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};

#endif // MESH_H
