#define GL_GLEXT_PROTOTYPES
#include "object.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

Object::Object()
{
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      vbRecId = 0;
      vbRecSz = 0;
      ebCount = 0;

      pos = rotation = {0, 0, 0};
      scale = {1, 1, 1};
}

void Object::Init(const char *objPath)
{
      std::ifstream file(objPath);
      std::string buff;
      std::vector<float> vertices;
      std::vector<unsigned int> indices;
      unsigned int i = 0;
      while (std::getline(file, buff))
      {
            std::istringstream line(buff);
            char type;
            line >> type;
            if (type == 'v')
            {
                  float x, y, z;
                  line >> x >> y >> z;
                  vertices.push_back(x);
                  vertices.push_back(y);
                  vertices.push_back(z);
            }
            else if (type == 'f')
            {
                  unsigned int a, b, c;
                  line >> a >> b >> c;
                  indices.push_back(a - 1);
                  indices.push_back(b - 1);
                  indices.push_back(c - 1);
            }
      }
      file.close();
      this->CreateVBO(&vertices[0], vertices.size() * sizeof(float));
      this->AddVBAttrib(3, 3);
      this->CreateEBO(&indices[0], indices.size() * sizeof(unsigned int));
}

void Object::CreateVBO(float *vertices, GLsizeiptr size)
{
      this->Bind();
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
      this->Unbind();
}

void Object::AddVBAttrib(GLint size, GLint stride)
{
      this->Bind();
      glVertexAttribPointer(vbRecId, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(vbRecSz * sizeof(float)));
      glEnableVertexAttribArray(vbRecId);
      this->Unbind();
      vbRecId++;
      vbRecSz += size;
}

void Object::CreateEBO(unsigned int *indices, GLsizeiptr size)
{
      this->Bind();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
      ebCount = size / sizeof(unsigned int);
      this->Unbind();
}

void Object::AttachShader(unsigned int shader)
{
      this->Bind();
      this->shader = shader;
      glUseProgram(shader);
      transformPtr = glGetUniformLocation(this->shader, "transforms");
      scalePtr = glGetUniformLocation(this->shader, "scales");
      rotationPtr = glGetUniformLocation(this->shader, "rotation");
      this->Unbind();
}

void Object::Render()
{
      this->Bind();
      glUniform3f(scalePtr, scale.x, scale.y, scale.z);
      glUniform3f(transformPtr, pos.x, pos.y, pos.z);
      glUniform3f(rotationPtr, rotation.x, rotation.y, rotation.z);
      glDrawElements(GL_TRIANGLES, ebCount, GL_UNSIGNED_INT, 0);
      this->Unbind();
}

void Object::Rescale(vec3 scale)
{
      this->scale = scale;
}
void Object::Rotate(vec3 rotation)
{
      this->rotation = rotation;
}
void Object::Respawn(vec3 pos)
{
      this->pos = pos;
}

void Object::Bind()
{
      glBindVertexArray(VAO);
}
void Object::Unbind()
{
      glBindVertexArray(0);
}

unsigned int Object::GetShader()
{
      return shader;
}

Object::~Object()
{
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
}