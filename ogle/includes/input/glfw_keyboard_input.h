/**
 * @file glfw_keyboard_input.h
 * @brief Defines KeyboardInput.
 */

#pragma once

#include "std/ogle_std.inc"
#include "input/keyboard_input.h"

// Opaque struct type from GLFW.
class GLFWwindow;

namespace ogle {

/**
 * @brief Collects keyboard input using GLFW.
 */
class GLFWKeyboardInput : public KeyboardInput {
 public:
  /// String to specify use of this implementation in configuration file.
  static const stl_string kConfigImplementationName;

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
  static const stl_unordered_map<int, KeyCode> key_mapping_;

  /**
   * @brief Callback passed to GLFW to record key actions.
   *
   * The interface is defined by GLFW. See
   * http://www.glfw.org/docs/latest/input.html.
   */
  static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode,
                              int action, int mods);

  /// Action occurring on each key.
  /// Static definition implies that only one keyboard is supported at a time.
  static stl_unordered_map<KeyCode, KeyAction, KeyCodeHash> key_actions_;
};

}  // namespace ogle

