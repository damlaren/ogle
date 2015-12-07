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

GLFWApplication::GLFWApplication() : Application(),
    window_(std::make_unique<ogle::GLFWWindow>()),
    renderer_(std::make_unique<ogle::GLFWRenderer>()) {
  // TODO(damlaren): Doesn't belong here. Abstract out.
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

GLFWApplication::~GLFWApplication() {
}

bool GLFWApplication::ApplicationBody() {
  window_->ClearWindow();
  window_->SwapBuffers();
  return window_->HandleWindowEvents();
}

}  // namespace ogle
