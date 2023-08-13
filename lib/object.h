#ifndef OBJECT__H___
#define OBJECT__H___

#include <GL/gl.h>

struct vec3 {
      float x,y,z;
};

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
      GLint transformPtr;
      GLint scalePtr;
      GLint rotationPtr;

      vec3 pos;
      vec3 scale;
      vec3 rotation;

public:
      Object();
      void Init(const char* objPath);
      void CreateVBO(float *vertices, GLsizeiptr size);
      void AddVBAttrib(GLint size, GLint stride);
      void CreateEBO(unsigned int *indices, GLsizeiptr size);
      void AttachShader(unsigned int shader);
      void Render();
      void Rescale(vec3 scale);
      void Rotate(vec3 rotation);
      void Respawn(vec3 pos);
      void Bind();
      void Unbind();

      unsigned int GetShader();

      ~Object();
};

#endif