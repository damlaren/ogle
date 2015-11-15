/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Window class.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_WINDOW_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_WINDOW_H_

#include <exception>

namespace ogle {

/**
 * @brief A Window that provides a rendering context.
 * It is assumed that there is only window per application.
 * Windows also handle events like closing and minimizing.
 */
class Window {
 public:
  /// Default constructor.
  Window() = default;

  /// Default destructor.
  virtual ~Window() = default;

  /// Swap buffers to display next frame.
  virtual void SwapBuffers() = 0;

  /**
   * @brief Handle events on window, like close.
   * @return false if window should close, else true.
   */
  virtual bool HandleWindowEvents() = 0;

 protected:
  /**
   * @brief Exception class that can be thrown if construction fails.
   * @details This exception is intended to halt the application in case
   * of an unrecoverable error during construction.
   */
  class WindowException : public std::exception {
  };
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_WINDOW_H_
