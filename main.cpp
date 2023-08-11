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
          -0.5f, -0.5f, // 0
          0.5f, -0.5f,  // 1
          0.5f, 0.5f,   // 2
          -0.5f, 0.5f,  // 3
      };

      unsigned int indices[] = {
          0, 1, 2, // 1
          0, 3, 2, // 2
      };

      Object *o = new Object();
      o->CreateVBO(vertices, sizeof(vertices));
      o->AddVBAttrib(0, 2, 2 * sizeof(float), (void *)0);
      o->CreateEBO(indices, sizeof(indices));

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
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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