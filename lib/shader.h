#ifndef SHADER__H___
#define SHADER__H___

#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Pipeline
{
private:
      unsigned int shaderProgram;
      unsigned int vertex;
      unsigned int fragment;

public:
      Pipeline();
      void reset();
      void AttachVertexShader(std::string path);
      void AttachFragmentShader(std::string path);
      unsigned int Build();
};

#endif