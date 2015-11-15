/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of glfw_window.h.
 */

#include "renderer/glfw_window.h"

#include "easylogging++.h"  // NOLINT
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace ogle{

GLFWWindow::GLFWWindow() :
    Window() {
  window_ = nullptr;
  if (!glfwInit()) {
    LOG(ERROR) << "Failed to init GLFW.";
    throw Window::WindowException();
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
    LOG(ERROR) << "Failed to create GLFW window.";
    throw Window::WindowException();
  }

  // TODO(damlaren): only one thread can have the context at once.
  glfwMakeContextCurrent(window_);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    glfwDestroyWindow(window_);
    glfwTerminate();
    LOG(ERROR) << "glewInit failed.";
    throw Window::WindowException();
  }

  glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
}

GLFWWindow::~GLFWWindow() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void GLFWWindow::SwapBuffers() {
  glfwSwapBuffers(window_);
}

bool GLFWWindow::HandleWindowEvents() {
  glfwPollEvents();

  if (glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
      glfwWindowShouldClose(window_) == 0) {
    return true;
  } else {
    return false;
  }
}

}  // namespace ogle