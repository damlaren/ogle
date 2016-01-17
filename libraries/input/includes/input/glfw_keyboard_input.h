/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines KeyboardInput.
 */

#ifndef LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H_
#define LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H_

#include <unordered_map>
#include "input/keyboard_input.h"

// Opaque struct type from GLFW.
class GLFWwindow;

namespace ogle {

/**
 * @brief Collects keyboard input using GLFW.
 */
class GLFWKeyboardInput : public KeyboardInput {
 public:
  void Clear() override;

  const bool IsKeyDown(const KeyCode code, const bool repeat) override;

  const bool IsKeyUp(const KeyCode code) override;

  /**
   * @brief Listen to events on a GLFW window.
   * @param window GLFWwindow (GLFW type, not the ogle class!) to
   *        attach this keyboard to.
   */
  void AttachToWindow(GLFWwindow* window);

 protected:
  /// Mapping from KeyCode to GLFW code.
  static const std::unordered_map<int, KeyCode> key_mapping_;

  /**
   * @brief Callback passed to GLFW to record key actions.
   *
   * The interface is defined by GLFW. See
   * http://www.glfw.org/docs/latest/input.html.
   */
  static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode,
                              int action, int mods);

  // TODO(damlaren): Only one keyboard is supported.
  /// Action occurring on each key.
  static std::unordered_map<KeyCode, KeyAction, KeyCodeHash> key_actions_;
};

}  // namespace ogle

#endif  // LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H_