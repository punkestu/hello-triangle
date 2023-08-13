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
GLint ratioPtr;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    ratio = float(height)/float(width);
    glUniform1f(ratioPtr, ratio);
}

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
          -0.5f, -0.5f, 0.5f, 1.0, 0.0, 0.0,  // 0
          0.5f, -0.5f, 0.5f, 0.0, 1.0, 0.0,   // 1
          0.5f, 0.5f, 0.5f, 0.0, 0.0, 1.0,    // 2
          -0.5f, 0.5f, 0.5f, 1.0, 1.0, 0.0,   // 3
                                              // back
          -0.5f, -0.5f, -0.5f, 0.0, 1.0, 1.0, // 0
          0.5f, -0.5f, -0.5f, 1.0, 0.0, 1.0,  // 1
          0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0,   // 2
          -0.5f, 0.5f, -0.5f, 0.0, 0.0, 0.0,  // 3
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
      o->Init("../teapot.obj");
      // o->CreateVBO(vertices, sizeof(vertices));
      // o->AddVBAttrib(3, 6);
      // o->AddVBAttrib(3, 6);
      // o->CreateEBO(indices, sizeof(indices));
      Object *o2 = new Object();
      o2->Init("../teapot.obj");

      Pipeline builder;
      builder.AttachVertexShader("../shaders/vertex.vert");
      builder.AttachFragmentShader("../shaders/fragment.frag");

      o->AttachShader(builder.Build());
      o2->AttachShader(o->GetShader());
      
      ratioPtr = glGetUniformLocation(o->GetShader(), "ratio");
      glUniform1f(ratioPtr, ratio);
      
      GLint camPosPtr = glGetUniformLocation(o->GetShader(), "camPos");
      glm::vec3 camPos = glm::vec3(0.f, 0.5f, 1.f);
      glUniform3f(camPosPtr, camPos.x, camPos.y, camPos.z);

      GLint camDirPtr = glGetUniformLocation(o->GetShader(), "camDir");
      glm::vec3 camDir = glm::vec3(0.f, 0.f, 0.f);
      glUniform3f(camDirPtr, camDir.x, camDir.y, camDir.z);

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_MULTISAMPLE);
      glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

      o->Rescale({0.1f,0.1f,0.1f});
      o->Respawn({-0.5f,0,0});
      o2->Rescale({0.1f,0.1f,0.1f});
      o2->Respawn({0.5f,0,0});

      float angY = 0;

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window))
      {
            o->Rotate({0,angY,0});
            o2->Rotate({0,angY,0});
            angY+=0.01f;
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                  glfwSetWindowShouldClose(window, 1);
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            o->Render();
            o2->Render();

            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      delete o;
      delete o2;
      builder.reset();
      glDeleteProgram(o->GetShader());
      glfwTerminate();
      return 0;
}