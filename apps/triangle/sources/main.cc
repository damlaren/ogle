/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines an app to display a triangle on the screen.
 * Used to validate primitive drawing code.
 */

/**
 * @brief main Main entry point.
 * @return 0 on success, something else on failure.
 */

#include "ogle/ogle.h"

using GLFWApplication = ogle::application::GLFWApplication;

/**
 * @brief Application for drawing a triangle.
 */
class TriangleApplication : public GLFWApplication {
 public:
  TriangleApplication() : GLFWApplication() {
  }
  ~TriangleApplication() override {
  }

  bool ApplicationBody() {
    return GLFWApplication::ApplicationBody();
  }
};

int main(const int argc, const char* argv[]) {
  auto app = std::make_unique<TriangleApplication>();
  app->RunApplication();
  return 0;
}
