#ifndef OBJECT__H___
#define OBJECT__H___

#include <GL/gl.h>

class Object
{
private:
      unsigned int VAO;
      unsigned int VBO;
      unsigned int EBO;

      unsigned int vbRecId;
      int vbRecSz;
      unsigned int ebCount;

      unsigned int shader;

public:
      Object();
      void Init(const char* objPath);
      void CreateVBO(float *vertices, GLsizeiptr size);
      void AddVBAttrib(GLint size, GLint stride);
      void CreateEBO(unsigned int *indices, GLsizeiptr size);
      void AttachShader(unsigned int shader);
      void Render();
      void Bind();
      void Unbind();

      unsigned int GetShader();

      ~Object();
};

#endif