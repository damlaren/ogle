/**
 * @file window.h
 * @brief Defines Window.
 */

#pragma once

#include "std/ogle_std.inc"
#include <memory>

namespace ogle {

class Configuration;

/**
 * @brief A window that provides a rendering context.
 *
 * It is assumed that there is only Window per application.
 * Windows also handle events like closing, minimizing,
 * and resizing.
 */
class Window {
 public:
  /// Configuration module for windows.
  static const stl_string kConfigModule;

  /// Configuration attribute defining implementation to use.
  static const stl_string kConfigAttributeImplementation;

  //@{
  /// Configuration attribute defining a common window property.
  static const stl_string kConfigAttributeWidth;
  static const stl_string kConfigAttributeHeight;
  static const stl_string kConfigAttributeTitle;
  //@}

  /**
   * @brief Default destructor.
   */
  virtual ~Window() = default;

  /**
   * @brief Creates a new Window.
   * @param configuration Window configuration.
   * @return New window.
   */
  static std::unique_ptr<Window> Build(const Configuration& configuration);

  /**
   * @brief Clear all window contents.
   */
  virtual void ClearWindow() = 0;

  /**
   * @brief Swap buffers to display next frame.
   */
  virtual void SwapBuffers() = 0;

  /**
   * @brief Handle events on window, like close.
   * @return false if window should close, else true.
   */
  virtual bool HandleWindowEvents() = 0;

  /**
   * @brief Accessor.
   * @return Window's aspect ratio.
   */
  virtual const float aspect_ratio() const = 0;

  /**
   * @brief Accessor.
   * @return Window width [pixels].
   */
  virtual const int window_width() const = 0;

  /**
   * @brief Accessor.
   * @return Window height [pixels].
   */
  virtual const int window_height() const = 0;
};

}  // namespace ogle

