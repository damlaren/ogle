/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLFWWindow class.
 */

#ifndef LIBRARIES_APPLICATION_INCLUDES_APPLICATION_GLFW_APPLICATION_H  // NOLINT
#define LIBRARIES_APPLICATION_INCLUDES_APPLICATION_GLFW_APPLICATION_H  // NOLINT

#include <memory>
#include <string>

#include "application/application.h"
#include "renderer/glfw_window.h"

namespace ogle {

/**
 * @brief An Application built using GLFW and GLEW.
 *
 * GLFW manages the window and input. GLEW manages OpenGL extensions.
 * AFAIK, this implies that this can only be an OpenGL application.
 */
class GLFWApplication : public Application {
 public:
  /**
   * @brief Initializes a generic application using GLFW.
   * @param[in] window Window to use for render output.
   * @param[in] resource_dir Resource directory location.
   */
  GLFWApplication(std::unique_ptr<GLFWWindow> window,
                  const std::string& resource_dir);

  /**
   * @brief Destructor.
   */
  ~GLFWApplication() override;

  /**
   * @brief Stub application body.
   *
   * Does nothing except check if escape key has been pressed.
   *
   * @return true until escape key is pressed.
   */
  bool ApplicationBody() override;

 protected:
  /// Window controlled by this application.
  std::unique_ptr<ogle::GLFWWindow> window_;
};

}  // namespace ogle

#endif  // LIBRARIES_APPLICATION_INCLUDES_APPLICATION_GLFW_APPLICATION_H  // NOLINT

