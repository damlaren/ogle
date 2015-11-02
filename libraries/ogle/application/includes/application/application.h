/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBRARIES_OGLE_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT
#define LIBRARIES_OGLE_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_  // NOLINT

/**
 * @file
 *
 * Application display window and graphics API context.
 */

namespace ogle {

namespace application {

/**
 * @brief Display context for entire application.
 *
 * This includes many different concepts right now, including:
 * 1) The display window.
 * 2) A callback for running the application.
 * 3) OpenGL extension querying.
 * 4) OpenGL settings configuration.
 *
 * They are lumped together because with some implementations
 * (GLFW + GLEW) these appear hard to separate.
 */
class Application {
 public:

 protected:
  /**
   * @brief Hidden constructor.
   */
  Application();
};

}  // namespace application

}  // namespace ogle

#endif  // LIBRARIES_OGLE_APPLICATION_INCLUDES_APPLICATION_APPLICATION_H_
