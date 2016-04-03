/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines KeyboardInput.
 */

#ifndef LIBRARIES_INPUT_INCLUDES_INPUT_KEYBOARD_INPUT_H_
#define LIBRARIES_INPUT_INCLUDES_INPUT_KEYBOARD_INPUT_H_

#include "std/ogle_std.inc"
#include <functional>

namespace ogle {

/**
 * @brief Actions for which to report keyboard input.
 */
enum class KeyAction {
  NONE,  // Nothing is being done to the key.
  PRESS,  // Key is being pushed down for the first time.
  HOLD,  // Key is being held down.
  RELEASE  // Key is moving back up.
};

/**
 * @brief Cross-platform keycodes.
 *
 * A commonly-used subset is defined, but this class can be expanded
 * as needed.
 */
enum class KeyCode {
  W,
  S,
  A,
  D,
  Q,
  E,
  Z,
  C,
  UP_ARROW,
  DOWN_ARROW,
  LEFT_ARROW,
  RIGHT_ARROW,
  ENTER,
  SPACE,
  LEFT_SHIFT,
  RIGHT_SHIFT,
  TAB,
  ESCAPE
};

/**
 * @brief Hash function object for KeyCode.
 */
struct KeyCodeHash {
 public:
  std::size_t operator()(const KeyCode code) const;
};

/**
 * @brief Class to collect input from keyboard.
 *
 * Subclasses use a specific API to set keyboard values.
 */
class KeyboardInput {
 public:
  /**
   * @brief Default destructor.
   */
  virtual ~KeyboardInput() = default;

  /**
   * @brief Clears internal state.
   */
  virtual void Clear() = 0;

  /**
   * @brief Checks if a key is down.
   * @param code Key code to check.
   * @param repeat If true, return true while the key is pressed. Otherwise
   *        return true only when it first goes down.
   * @return true if down.
   */
  virtual const bool IsKeyDown(const KeyCode code, const bool repeat) = 0;

  /**
   * @brief Checks if a key just went up.
   * @param code Key code to check.
   * @return true if up.
   */
  virtual const bool IsKeyUp(const KeyCode code) = 0;

  /**
   * @brief Check if either the right or left Shift key is down.
   * @param repeat Same function as the @p repeat parameter for IsKeyDown.
   */
  const bool IsShiftDown(const bool repeat);
};

}  // namespace ogle

#endif  // LIBRARIES_INPUT_INCLUDES_INPUT_KEYBOARD_INPUT_H_
