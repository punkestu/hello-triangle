#define GL_GLEXT_PROTOTYPES
#include "shader.h"

std::string readFile(std::string path)
{
      std::ifstream file(path);
      if (file)
      {
            std::stringstream ss;
            ss << file.rdbuf();
            std::string buffer = ss.str();
            return buffer;
      }
      std::cout << path << " not found" << std::endl;
      return "";
}

void getShaderCompileError(unsigned int shader, GLenum type)
{
      int success;
      char infoLog[512];

      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : (type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "")) << "::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
      }
}

Pipeline::Pipeline()
{
      vertex = 0;
      fragment = 0;
}

void Pipeline::reset()
{
      if (vertex > 0)
      {
            glDeleteShader(vertex);
      }
      if (fragment > 0)
      {
            glDeleteShader(fragment);
      }
      vertex = 0;
      fragment = 0;
}

void Pipeline::AttachVertexShader(std::string path)
{
      std::string codeStr = readFile(path);
      const char *code = codeStr.c_str();
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &code, NULL);
      glCompileShader(vertex);
      getShaderCompileError(vertex, GL_VERTEX_SHADER);
}

void Pipeline::AttachFragmentShader(std::string path)
{
      std::string codeStr = readFile(path);
      const char *code = codeStr.c_str();
      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &code, NULL);
      glCompileShader(fragment);
      getShaderCompileError(fragment, GL_FRAGMENT_SHADER);
}

unsigned int Pipeline::Build()
{
      unsigned int shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertex);
      glAttachShader(shaderProgram, fragment);
      glLinkProgram(shaderProgram);
      return shaderProgram;
}

Pipeline::~Pipeline()
{
      this->reset();
}