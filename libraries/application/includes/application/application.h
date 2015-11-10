/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT
#define LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT

/**
 * @file Provides Application.
 */

namespace ogle {

namespace application {

/**
 * @brief Display context for entire application. It's assumed only one is created.
 *
 * This class wraps many things right now:
 * 1) The display window.
 * 2) A callback for running the application.
 * 3) OpenGL extension querying.
 * 4) OpenGL settings configuration.
 *
 * This is because these facets are entangled in some implementations (GLFW + GLEW).
 */
class Application {
 public:
  /**
   * @brief Executes application start, body (in a loop), and end.
   */
  void RunApplication();

 protected:
  /**
   * @brief Constructor.
   */
  Application();

  /**
   * @brief Destructor.
   * Responsible for releasing all resources reserved by the Application.
   */
  virtual ~Application();

  /**
   * @brief Function to execute in main loop, with minimal restrictions imposed.
   * @return true to run next loop iteration, false to stop.
   */
  virtual bool ApplicationBody() = 0;
};

}  // namespace application

}  // namespace ogle

#endif  // LIBRARIES_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_
