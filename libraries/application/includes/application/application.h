/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT
#define LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT

#include <exception>
#include <memory>
#include <string>
#include "input/keyboard_input.h"
#include "renderer/window.h"
#include "resource/resource_manager.h"

/**
 * @file Defines Application.
 */

namespace ogle {

/**
 * @brief Base class for all ogle applications.
 *
 * All applications are implemented as children of this class, by overriding
 * the #ApplicationBody member.
 */
class Application {
 public:
  /**
   * @brief A generic exception that can be thrown when an app fails.
   */
  class RuntimeException : public std::exception {
    // TODO(damlaren): actually, there are good reasons not to use exceptions--
    // most game engines disable them. Think about this more.
  };

  /**
   * @brief The entry point and main loop of the Application.
   *
   * It takes the following steps:
   *
   * TODO(damlaren): describe
   *
   * - Executes #ApplicationBody while it returns true.
   */
  void RunApplication();

 protected:
  /**
   * @brief Constructor.
   *
   * unique_ptr parameters refer to objects the Application will take ownership
   * over. They are invalid after constructing the Application.
   *
   * @param resource_manager ResourceManager implementation.
   * @param window Window implementation.
   * @param keyboard KeyboardInput implementation.
   */
  explicit Application(std::unique_ptr<ResourceManager> resource_manager,
                       std::unique_ptr<Window> window,
                       std::unique_ptr<KeyboardInput> keyboard);

  /**
   * @brief Destructor.
   *
   * Responsible for releasing all objects owned by the Application.
   */
  virtual ~Application() = default;

  /**
   * @brief Function to execute in main loop.
   * @return true to run next loop iteration, false to stop.
   */
  virtual bool ApplicationBody() = 0;

  /// Application's ResourceManager.
  std::unique_ptr<ResourceManager> resource_manager_;

  /// Application's Window.
  std::unique_ptr<ogle::Window> window_;

  /// Application's KeyboardInput.
  std::unique_ptr<ogle::KeyboardInput> keyboard_;

  // TODO(damlaren) RenderManager, InputManager passed instead.

  /// How many times the body has completed.
  std::uint64_t loop_count_ = 0;
};

}  // namespace ogle

#endif  // LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_
