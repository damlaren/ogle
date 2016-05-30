/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of window.h.
 */

#include "renderer/window.h"
#include "config/configuration.h"
#include "renderer/glfw_window.h"

namespace ogle {

const stl_string Window::kConfigModule = "window";
const stl_string Window::kConfigAttributeImplementation = "implementation";
const stl_string Window::kConfigAttributeWidth = "width";
const stl_string Window::kConfigAttributeHeight = "height";
const stl_string Window::kConfigAttributeTitle = "title";

std::unique_ptr<Window> Window::Build(const Configuration& configuration) {
  const stl_string implementation = configuration.Get<stl_string>(
      kConfigModule, kConfigAttributeImplementation);
  if (implementation == GLFWWindow::kConfigImplementationName) {
    auto new_object = AllocateUniqueObject<GLFWWindow>();
    const int width = configuration.Get<int>(
        kConfigModule, kConfigAttributeWidth);
    const int height = configuration.Get<int>(
        kConfigModule, kConfigAttributeHeight);
    const stl_string& title = configuration.Get<stl_string>(
        kConfigModule, kConfigAttributeTitle);
    const int opengl_major_version = configuration.Get<int>(
        kConfigModule, "opengl_major_version");
    const int opengl_minor_version = configuration.Get<int>(
        kConfigModule, "opengl_minor_version");
    const int msaa_samples = configuration.Get<int>(
        kConfigModule, "msaa_samples");
    if (new_object->Create(width, height, title, opengl_major_version,
                           opengl_minor_version, msaa_samples)) {
      return std::move(new_object);
    } else {
      LOG(ERROR) << "GLFWWindow Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create Window for implementation: "
             << implementation;
  return nullptr;
}

}  // namespace ogle
