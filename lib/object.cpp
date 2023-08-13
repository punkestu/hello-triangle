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
            std::stringstream ss(buff);
            std::string c;
            std::getline(ss, c, ' ');
            if (c == "v")
            {
                  while (std::getline(ss, c, ' '))
                  {
                        // std::cout<<std::stof(c)<<";";
                        vertices.push_back(std::stof(c));
                        // if(std::stof(c) > 0) {
                        //       std::cout<<"b";
                        // }
                  }
                  // std::cout<<std::endl;
            }
            else if (c == "f")
            {
                  while (std::getline(ss, c, ' '))
                  {
                        indices.push_back(std::stoul(c)-1);
                  }
            }
      }
      file.close();
      std::cout<<vertices.size()/3<<":"<<indices.size()/3<<std::endl;
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
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
      this->Unbind();
}

void Object::Render()
{
      this->Bind();
      glDrawElements(GL_TRIANGLES, ebCount, GL_UNSIGNED_INT, 0);
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

unsigned int Object::GetShader()
{
      return shader;
}

Object::~Object()
{
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
}