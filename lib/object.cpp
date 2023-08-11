#define GL_GLEXT_PROTOTYPES
#include "object.h"

Object::Object()
{
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
}

void Object::CreateVBO(float *vertices, GLsizeiptr size)
{
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
      glBindVertexArray(0);
}

void Object::AddVBAttrib(GLuint id, GLint size, GLsizei stride, const void *offset)
{
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, stride, offset);
      glEnableVertexAttribArray(id);
      glBindVertexArray(0);
}

void Object::AttachShader(unsigned int shader) {
      this->Bind();
      glUseProgram(shader);
      this->Unbind();
}

void Object::Bind()
{
      glBindVertexArray(VAO);
}
void Object::Unbind()
{
      glBindVertexArray(0);
}

Object::~Object()
{
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
}