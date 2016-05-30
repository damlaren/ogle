/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef OGLE_INCLUDES_APPLICATION_APPLICATION_H_
#define OGLE_INCLUDES_APPLICATION_APPLICATION_H_

#include "std/ogle_std.inc"
#include "engine/engine.h"

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
   * @brief The entry point and main loop of the Application.
   *
   * It takes the following steps while ApplicationBody() returns true:
   * - Calls #HandleWindowEvents on its Window, exits if it returns false.
   * - Calls #ApplicationBody.
   */
  void RunApplication();

 protected:
  /**
   * @brief Constructor.
   *
   * It exists to receive passed resources. It should not do any other
   * initialization-- that is the responsibility of #Create().
   *
   * unique_ptr parameters refer to objects the Application will take ownership
   * over. They are invalid after constructing the Application.
   *
   * @param engine ogle Engine object.
   */
  explicit Application(std::unique_ptr<Engine> engine);

  /**
   * @brief Destructor.
   *
   * Responsible for releasing all objects owned by the Application.
   */
  virtual ~Application() = default;

  /**
   * @brief Creates a usable Application.
   * @return success or failure.
   */
  virtual bool Create() = 0;

  /**
   * @brief Function to execute in main loop.
   * @return true to run next loop iteration, false to stop.
   */
  virtual bool ApplicationBody() = 0;

  /// ogle Engine object.
  std::unique_ptr<Engine> engine_;

  /// How many times the body has completed.
  std::uint64_t loop_count_ = 0;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_APPLICATION_APPLICATION_H_
