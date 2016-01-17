/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of glfw_keyboard_input.h.
 */

#include "input/glfw_keyboard_input.h"
#include "easylogging++.h"  // NOLINT
#include "GLFW/glfw3.h"

namespace ogle {

const std::map<KeyCode, int> GLFWKeyboardInput::key_mapping_ = {
  {KeyCode::W, GLFW_KEY_W},
  {KeyCode::S, GLFW_KEY_S},
  {KeyCode::A, GLFW_KEY_A},
  {KeyCode::D, GLFW_KEY_D},
  {KeyCode::Q, GLFW_KEY_Q},
  {KeyCode::E, GLFW_KEY_E},
  {KeyCode::Z, GLFW_KEY_Z},
  {KeyCode::C, GLFW_KEY_C},
  {KeyCode::UP_ARROW, GLFW_KEY_UP},
  {KeyCode::DOWN_ARROW, GLFW_KEY_DOWN},
  {KeyCode::LEFT_ARROW, GLFW_KEY_LEFT},
  {KeyCode::RIGHT_ARROW, GLFW_KEY_RIGHT},
  {KeyCode::ENTER, GLFW_KEY_ENTER},
  {KeyCode::SPACE, GLFW_KEY_SPACE},
  {KeyCode::LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT},
  {KeyCode::RIGHT_SHIFT, GLFW_KEY_RIGHT_SHIFT},
  {KeyCode::TAB, GLFW_KEY_TAB},
  {KeyCode::ESCAPE, GLFW_KEY_ESCAPE},
};

const bool GLFWKeyboardInput::IsKeyDown(const KeyCode code,
                                        const bool repeat) {
  int glfw_code = GetGLFWKeyCode(code);
  int glfw_action = repeat? GLFW_REPEAT : GLFW_PRESS;
  if (glfw_code != kUnmappedCode) {
    return glfwGetKey(window_, glfw_code) == glfw_action;
  }
  return false;
}

const bool GLFWKeyboardInput::IsKeyUp(const KeyCode code) {
  int glfw_code = GetGLFWKeyCode(code);
  if (glfw_code != kUnmappedCode) {
    return glfwGetKey(window_, glfw_code) == GLFW_RELEASE;
  }
  return false;
}

void GLFWKeyboardInput::AttachToWindow(GLFWwindow* window) {
  window_ = window;
  if (window_ == nullptr) {
    LOG(ERROR) << "Cannot attach keyboard to null window.";
  }
}

const int GLFWKeyboardInput::GetGLFWKeyCode(const KeyCode code) {
  auto iterator = key_mapping_.find(code);
  if (iterator != key_mapping_.end()) {
    return iterator->second;
  }
  LOG(ERROR) << "Unrecognized KeyCode: " << static_cast<int>(code);
  return kUnmappedCode;
}

}  // namespace ogle
