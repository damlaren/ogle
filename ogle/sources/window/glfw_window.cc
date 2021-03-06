/**
 * @file glfw_window.cc
 * @brief Implementation of glfw_window.h.
 */

#include "window/glfw_window.h"
#include "easylogging++.h"  // NOLINT
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "input/glfw_keyboard_input.h"

namespace ogle {

const stl_string GLFWWindow::kConfigImplementationName = "glfw";

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

  glfwSetFramebufferSizeCallback(window_, GLFWWindow::FramebufferSizeCallback);

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

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

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
  int width, height;
  glfwGetFramebufferSize(window_, &width, &height);
  if (width < 0 || height < 0) {
    LOG(ERROR) << "Computing invalid aspect ratio for window with FB size "
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

void GLFWWindow::FramebufferSizeCallback(GLFWwindow *window,
                                         int width, int height) {
  glViewport(0, 0, width, height);

  // TODO(damlaren): Send event that Camera can receive to update aspect ratio.
}

}  // namespace ogle
