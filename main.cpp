#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "lib/object.h"
#include "lib/shader.h"

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
          -0.5f,
          -0.5f,
          0.0f,
          0.0f,
          0.5f,
          -0.5f,
          0.0f,
          0.0f,
          0.0f,
          0.5f,
          0.0f,
          0.0f,
      };

      Object *o = new Object();
      o->CreateVBO(vertices, sizeof(vertices));
      o->AddVBAttrib(0, 3, 4 * sizeof(float), (void *)0);

      Pipeline builder;
      builder.reset();
      builder.AttachVertexShader("../shaders/vertex.vert");
      builder.AttachFragmentShader("../shaders/fragment.frag");
      unsigned int shaderProgram = builder.Build();

      o->AttachShader(shaderProgram);

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
            o->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
      }

      delete o;
      glDeleteProgram(shaderProgram);
      glfwTerminate();
      return 0;
}