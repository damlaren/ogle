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

GLFWApplication::GLFWApplication(
    std::unique_ptr<ogle::GLFWWindow> window,
    std::unique_ptr<ogle::GLFWKeyboardInput> keyboard,
    const std::string& resource_dir)
  : Application(resource_dir), window_(std::move(window)),
    keyboard_(std::move(keyboard)) {
  window_->AttachKeyboard(keyboard_.get());
}

GLFWApplication::~GLFWApplication() {
}

bool GLFWApplication::ApplicationBody() {
  window_->ClearWindow();
  window_->SwapBuffers();
  if (!window_->HandleWindowEvents() ||
      keyboard_->IsKeyDown(KeyCode::ESCAPE, false)) {
    return false;
  }

  ++loop_count_;
  return true;
}

}  // namespace ogle
