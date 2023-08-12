#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include "lib/object.h"
#include "lib/shader.h"

float ratio;

int main()
{

      GLFWwindow *window;

      if (!glfwInit())
            return -1;

      window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
      if (!window)
      {
            glfwTerminate();
            return -1;
      }

      glfwMakeContextCurrent(window);
      glfwWindowHint(GLFW_SAMPLES, 4);
      ratio = 480.f / 640.f;

      float vertices[] = {
          // =================================== front
          -0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0,  // 0
          0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0,   // 1
          0.5f, 0.5f, 0.5f, 1.0, 1.0, 1.0,    // 2
          -0.5f, 0.5f, 0.5f, 1.0, 1.0, 1.0,   // 3
                                              // back
          -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, // 0
          0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,  // 1
          0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0,   // 2
          -0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0,  // 3
      };

      unsigned int indices[] = {
          0, 1, 2, // 1
          0, 3, 2, // 2
          1, 5, 2, // 3
          2, 6, 5, // 4
          5, 4, 7, // 5
          5, 6, 7, // 6
          7, 3, 4, // 7
          4, 0, 3, // 8
          3, 7, 6, // 9
          3, 2, 6, // 10
          0, 1, 5, // 11
          0, 4, 5  // 12
      };

      Object *o = new Object();
      o->CreateVBO(vertices, sizeof(vertices));
      o->AddVBAttrib(3, 6);
      o->AddVBAttrib(3, 6);
      o->CreateEBO(indices, sizeof(indices));

      Pipeline builder;
      builder.AttachVertexShader("../shaders/vertex.vert");
      builder.AttachFragmentShader("../shaders/fragment.frag");

      o->AttachShader(builder.Build());
      GLint ratioPtr = glGetUniformLocation(o->GetShader(), "ratio");
      glUniform1f(ratioPtr, ratio);
      glm::vec3 rotation = glm::vec3(0.f, 1.f, 0.f);
      GLint rotationPtr = glGetUniformLocation(o->GetShader(), "rotateAx");
      glUniform3f(rotationPtr, rotation.x, rotation.y, rotation.z);
      float rotationAngle = 45.f;
      GLint anglePtr = glGetUniformLocation(o->GetShader(), "angle");
      glm::vec3 pos = glm::vec3(0.f, 0.f, -1.f);
      GLint cameraPtr = glGetUniformLocation(o->GetShader(), "camera");
      glUniform3f(cameraPtr, pos.x, pos.y, pos.z);

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_MULTISAMPLE);

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window))
      {

            glUniform1f(anglePtr, glm::radians(rotationAngle));
            glUniform3f(cameraPtr, pos.x, pos.y, pos.z);
            rotationAngle++;
            // pos.z -= 0.01f;
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                  glfwSetWindowShouldClose(window, 1);
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            o->Render();

            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      delete o;
      builder.reset();
      // delete o2;
      glDeleteProgram(o->GetShader());
      glfwTerminate();
      return 0;
}