/**
 * @file Defines KeyboardInput.
 */

#ifndef OGLE_INCLUDES_INPUT_KEYBOARD_INPUT_H_
#define OGLE_INCLUDES_INPUT_KEYBOARD_INPUT_H_

#include "std/ogle_std.inc"
#include <functional>
#include <memory>

namespace ogle {

class Configuration;
class Window;

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
  std::size_t operator()(const KeyCode code) const;
};

/**
 * @brief Class to collect input from keyboard.
 *
 * Subclasses use a specific API to set keyboard values.
 */
class KeyboardInput {
 public:
  /// Configuration module for input.
  static const stl_string kConfigModule;

  /// Configuration attribute defining implementation to use.
  static const stl_string kConfigAttributeImplementation;

  /**
   * @brief Default destructor.
   */
  virtual ~KeyboardInput() = default;

  /**
   * @brief Builds keyboard input handler.
   * @param configuration Configuration for keyboard input.
   * @param[in,out] window Window to associate with keyboard, if needed.
   * @return New KeyboardInput.
   */
  static std::unique_ptr<KeyboardInput> Build(
      const Configuration& configuration, Window* window);

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

#endif  // OGLE_INCLUDES_INPUT_KEYBOARD_INPUT_H_
