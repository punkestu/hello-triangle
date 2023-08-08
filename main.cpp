#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(std::string path)
{
      std::ifstream file(path);
      if (!file)
      {
            std::cout << "boooo" << std::endl;
      }
      std::stringstream ss;
      ss << file.rdbuf();
      std::string buffer = ss.str();
      return buffer;
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

int main()
{

      GLFWwindow *window;

      /* Initialize the library */
      if (!glfwInit())
            return -1;

      /* Create a windowed mode window and its OpenGL context */
      window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
      if (!window)
      {
            glfwTerminate();
            return -1;
      }

      /* Make the window's context current */
      glfwMakeContextCurrent(window);

      float vertices[] = {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f, 0.5f, 0.0f};

      unsigned int VBO;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
      glEnableVertexAttribArray(0);

      std::string bufferV = readFile("../shaders/vertex.vert");
      const char *vs = bufferV.c_str();

      std::string bufferF = readFile("../shaders/fragment.frag");
      const char *fs = bufferF.c_str();

      unsigned int vertexShader;
      unsigned int fragmentShader;
      unsigned int shaderProgram;

      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vs, NULL);
      glCompileShader(vertexShader);

      fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fs, NULL);
      glCompileShader(fragmentShader);

      getShaderCompileError(vertexShader, GL_VERTEX_SHADER);
      getShaderCompileError(fragmentShader, GL_FRAGMENT_SHADER);

      shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
      glLinkProgram(shaderProgram);
      glUseProgram(shaderProgram);

      glDeleteShader(vertexShader);

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window))
      {

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                  glfwSetWindowShouldClose(window, 1);
            }

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
      }

      glfwTerminate();
      return 0;
}