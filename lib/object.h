#ifndef OBJECT__H___
#define OBJECT__H___

#include <GL/gl.h>

class Object
{
private:
      unsigned int VAO;
      unsigned int VBO;

      unsigned int shader;

public:
      Object();
      void CreateVBO(float *vertices, GLsizeiptr size);
      void AddVBAttrib(GLuint id, GLint size, GLsizei stride, const void *offset);
      void AttachShader(unsigned int shader);
      void Bind();
      void Unbind();
      ~Object();
};

#endif