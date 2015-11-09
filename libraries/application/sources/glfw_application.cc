/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements glfw_application.h.
 */

#include "application/glfw_application.h"

#include "easylogging++.h"  // NOLINT
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace ogle {

namespace application {

GLFWApplication::GLFWApplication() : Application() {
  window_ = nullptr;
  if (!glfwInit()) {
    LOG(FATAL) << "Failed to init GLFW.";
  }

  // TODO(damlaren): Hardcoded parameters should be configurable.
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Deprecate old stuff.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(1024, 768, "My Window Title", nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    LOG(FATAL) << "Failed to create GLFW window.";
  }

  // TODO(damlaren): only one thread can have the context at once.
  glfwMakeContextCurrent(window_);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    LOG(FATAL) << "glewInit failed.";
  }
}

GLFWApplication::~GLFWApplication() {
  glfwTerminate();
}

bool GLFWApplication::ApplicationBody() {
  return true;
}

}  // namespace application

}  // namespace ogle
