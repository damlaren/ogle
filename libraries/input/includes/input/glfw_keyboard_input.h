/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines KeyboardInput.
 */

#ifndef LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H
#define LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H

#include <map>
#include "input/keyboard_input.h"

// Opaque struct type from GLFW.
class GLFWwindow;

namespace ogle {

/**
 * @brief Collects keyboard input using GLFW.
 */
class GLFWKeyboardInput : public KeyboardInput {
 public:
  const bool IsKeyDown(const KeyCode code, const bool only_on_change) override;

  const bool IsKeyUp(const KeyCode code) override;

  /**
   * @brief Listen to events on a GLFW window.
   * @param window GLFWwindow (GLFW type, not the ogle class!) to
   *        attach this keyboard to.
   */
  void AttachToWindow(GLFWwindow* window);

 protected:
  /// Mapping from KeyCode to GLFW code.
  static const std::map<KeyCode, int> key_mapping_;

  /// Error value when no GLFW mapping exists for a key code.
  static constexpr int kUnmappedCode = -1;

  /**
   * @brief Get GLFW code corresponding to @p code.
   * @param code .
   * @return GLFW code, or @p kUnmappedCode if not found.
   */
  static const int GetGLFWKeyCode(const KeyCode code);

 private:
  /// Window this keyboard is attached to. This is GLFW's GLFWwindow,
  /// not ogle's GLFWWindow!
  GLFWwindow *window_;
};

}  // namespace ogle

#endif  // LIBRARIES_INPUT_INCLUDES_INPUT_GLFW_KEYBOARD_INPUT_H
