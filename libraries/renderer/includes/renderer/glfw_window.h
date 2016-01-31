/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLFWWindow class.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_WINDOW_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_WINDOW_H_

#include <string>
#include "renderer/window.h"

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
  /**
   * @brief Default constructor (deleted).
   */
  GLFWWindow() = delete;

  /**
   * @brief Constructor.
   * @param width Initial window width [pixels].
   * @param height Initial window height [pixels].
   * @param title Window title.
   * @param opengl_major_version Major version number required from OpenGL.
   * @param opengl_minor_version Minor version number required from OpenGL.
   * @param msaa_samples Number of samples to use for MSAA (anti-aliasing).
   */
  GLFWWindow(const int width, const int height, const std::string& title,
             const int opengl_major_version, const int opengl_minor_version,
             const int msaa_samples);

  /**
   * @brief Destructor.
   */
  ~GLFWWindow() override;

  void ClearWindow() override;
  void SwapBuffers() override;
  bool HandleWindowEvents() override;

  /**
   * @brief Register keyboard to listen to events on this window.
   * @param keyboard GLFW keyboard to register..
   */
  void AttachKeyboard(GLFWKeyboardInput* keyboard);

 protected:
  /**
   * @brief Callback to log errors from GLFW.
   * @param error Error code.
   * @param description String description of error.
   */
  static void LogGLFWError(int error, const char *description);

  /**
   * GLFW's window implementation.
   * An opaque type which can't be stored in a smart pointer.
   */
  GLFWwindow* window_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_WINDOW_H_
