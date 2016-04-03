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
#include "input/glfw_keyboard_input.h"

namespace ogle {

GLFWWindow::GLFWWindow()
  : Window(), window_(nullptr) {
}

GLFWWindow::~GLFWWindow() {
  if (window_ != nullptr) {
    glfwDestroyWindow(window_);
  }
  glfwTerminate();
}

bool GLFWWindow::Create(
    const int width, const int height, const stl_string& title,
    const int opengl_major_version, const int opengl_minor_version,
    const int msaa_samples) {
  if (!glfwInit()) {
    LOG(ERROR) << "Failed to init GLFW.";
    return false;
  }

  glfwSetErrorCallback(LogGLFWError);
  glfwWindowHint(GLFW_SAMPLES, msaa_samples);  // Anti-aliasing.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_version);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_version);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Deprecate old stuff.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    LOG(ERROR) << "Failed to create GLFW window.";
    return false;
  }

  glfwMakeContextCurrent(window_);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    glfwDestroyWindow(window_);
    glfwTerminate();
    LOG(ERROR) << "glewInit failed.";
    return false;
  }

  glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
  return true;
}

void GLFWWindow::ClearWindow() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFWWindow::SwapBuffers() {
  glfwSwapBuffers(window_);
}

bool GLFWWindow::HandleWindowEvents() {
  glfwPollEvents();

  // TODO(damlaren): Doesn't belong here. Make configurable.
  // Or at least, need consistent behavior across implementations.
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);  // TODO(damlaren): Actually, should be CW... ?

  if (glfwWindowShouldClose(window_) == 0) {
    return true;
  } else {
    return false;
  }
}

void GLFWWindow::AttachKeyboard(GLFWKeyboardInput* keyboard) {
  keyboard->AttachToWindow(window_);
}

const float GLFWWindow::aspect_ratio() const {
  int width = window_width();
  int height = window_height();
  if (width < 0 || height < 0) {
    LOG(ERROR) << "Computing invalid aspect ratio for window of size "
               << width << "x" << height;
  }
  return static_cast<float>(width) / height;
}

const int GLFWWindow::window_width() const {
  int width, height;
  glfwGetWindowSize(window_, &width, &height);
  return width;
}

const int GLFWWindow::window_height() const {
  int width, height;
  glfwGetWindowSize(window_, &width, &height);
  return height;
}

void GLFWWindow::LogGLFWError(int error, const char *description) {
  LOG(ERROR) << "GLFW error code=" << error << ": " << description;
}

}  // namespace ogle
