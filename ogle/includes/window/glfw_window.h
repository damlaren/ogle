/**
 * @file glfw_window.h
 * @brief Defines GLFWWindow class.
 */

#pragma once

#include "std/ogle_std.inc"
#include "window/window.h"

class GLFWwindow;  // From GLFW.

namespace ogle {

class GLFWKeyboardInput;

/**
 * @brief Window implemented using GLFW.
 *
 * This is a rather unfortunate name, as GLFW includes the GLFWwindow class.
 * The ogle class is implemented using the GLFW class.
 */
class GLFWWindow : public Window {
 public:
  /// String to specify use of this implementation in configuration file.
  static const stl_string kConfigImplementationName;

  /**
   * @brief Constructor. #Create() must be called to build a usable Window.
   */
  GLFWWindow();

  /**
   * @brief Destructor.
   */
  ~GLFWWindow() override;

  /**
   * @brief Initializes Window based on parameters.
   * @param width Initial window width [pixels].
   * @param height Initial window height [pixels].
   * @param title Window title.
   * @param opengl_major_version Major version number required from OpenGL.
   * @param opengl_minor_version Minor version number required from OpenGL.
   * @param msaa_samples Number of samples to use for MSAA (anti-aliasing).
   * @return Success or failure.
   */
  bool Create(const int width, const int height, const stl_string& title,
              const int opengl_major_version, const int opengl_minor_version,
              const int msaa_samples);

  void ClearWindow() override;
  void SwapBuffers() override;
  bool HandleWindowEvents() override;

  /**
   * @brief Register keyboard to listen to events on this window.
   * @param keyboard GLFW keyboard to register..
   */
  void AttachKeyboard(GLFWKeyboardInput* keyboard);

  const float aspect_ratio() const override;

  /**
   * @brief Accessor. Can only be called from main thread.
   * @return Window width [pixels].
   */
  const int window_width() const override;

  /**
   * @brief Accessor. Can only be called from main thread.
   * @return Window height [pixels].
   */
  const int window_height() const override;

 protected:
  /**
   * @brief Callback to log errors from GLFW.
   * @param error Error code.
   * @param description String description of error.
   */
  static void LogGLFWError(int error, const char *description);

  /**
   * @brief Callback that's run when framebuffer changes size.
   * @param window GLFW window.
   * @param width New framebuffer size.
   * @param height New framebuffer height.
   */
  static void FramebufferSizeCallback(GLFWwindow* window,
                                      int width, int height);

  /**
   * GLFW's window implementation.
   * An opaque type which can't be stored in a smart pointer.
   */
  GLFWwindow* window_;
};

}  // namespace ogle

