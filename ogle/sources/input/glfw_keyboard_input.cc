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

const stl_unordered_map<int, KeyCode> GLFWKeyboardInput::key_mapping_ = {
  {GLFW_KEY_W, KeyCode::W},
  {GLFW_KEY_S, KeyCode::S},
  {GLFW_KEY_A, KeyCode::A},
  {GLFW_KEY_D, KeyCode::D},
  {GLFW_KEY_Q, KeyCode::Q},
  {GLFW_KEY_E, KeyCode::E},
  {GLFW_KEY_Z, KeyCode::Z},
  {GLFW_KEY_C, KeyCode::C},
  {GLFW_KEY_UP, KeyCode::UP_ARROW},
  {GLFW_KEY_DOWN, KeyCode::DOWN_ARROW},
  {GLFW_KEY_LEFT, KeyCode::LEFT_ARROW},
  {GLFW_KEY_RIGHT, KeyCode::RIGHT_ARROW},
  {GLFW_KEY_ENTER, KeyCode::ENTER},
  {GLFW_KEY_SPACE, KeyCode::SPACE},
  {GLFW_KEY_LEFT_SHIFT, KeyCode::LEFT_SHIFT},
  {GLFW_KEY_RIGHT_SHIFT, KeyCode::RIGHT_SHIFT},
  {GLFW_KEY_TAB, KeyCode::TAB},
  {GLFW_KEY_ESCAPE, KeyCode::ESCAPE},
};

const stl_string GLFWKeyboardInput::kConfigImplementationName = "glfw";

void GLFWKeyboardInput::Clear() {
  key_actions_.clear();
}

const bool GLFWKeyboardInput::IsKeyDown(const KeyCode code,
                                        const bool repeat) {
  const auto key_iterator = key_actions_.find(code);
  if (key_iterator != key_actions_.end()) {
    bool pressed = key_iterator->second == KeyAction::PRESS;
    bool held = key_iterator->second == KeyAction::HOLD;
    if (repeat) {
      return held || pressed;
    } else {
      return pressed;
    }
  }
  return false;
}

const bool GLFWKeyboardInput::IsKeyUp(const KeyCode code) {
  const auto key_iterator = key_actions_.find(code);
  if (key_iterator != key_actions_.end()) {
    return key_iterator->second == KeyAction::RELEASE;
  }
  return false;
}

void GLFWKeyboardInput::AttachToWindow(GLFWwindow* window) {
  if (window == nullptr) {
    LOG(ERROR) << "Cannot attach keyboard to null window.";
  } else {
    glfwSetKeyCallback(window, GLFWKeyCallback);
  }
}

void GLFWKeyboardInput::GLFWKeyCallback(GLFWwindow* window, int key,
                                        int scancode, int action, int mods) {
  const auto key_iterator = key_mapping_.find(key);
  if (key_iterator == key_mapping_.end()) {
    LOG(ERROR) << "No KeyCode found for GLFW key: " << key;
  } else {
    KeyAction mapped_action = KeyAction::NONE;
    switch (action) {
      case GLFW_PRESS: {
        mapped_action = KeyAction::PRESS;
        break;
      }
      case GLFW_REPEAT: {
        mapped_action = KeyAction::HOLD;
        break;
      }
      case GLFW_RELEASE: {
        mapped_action = KeyAction::RELEASE;
        break;
      }
      default: {
        LOG(ERROR) << "No KeyAction found for GLFW action: " << action;
      }
    }

    key_actions_[key_iterator->second] = mapped_action;
  }
}

stl_unordered_map<KeyCode, KeyAction, KeyCodeHash>
    GLFWKeyboardInput::key_actions_;

}  // namespace ogle
