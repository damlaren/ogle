/**
 * @file Implementation of window.h.
 */

#include "window/window.h"
#include "config/configuration.h"
#include "window/glfw_window.h"

namespace ogle {

const stl_string Window::kConfigModule = "window";
const stl_string Window::kConfigAttributeImplementation = "implementation";
const stl_string Window::kConfigAttributeWidth = "width";
const stl_string Window::kConfigAttributeHeight = "height";
const stl_string Window::kConfigAttributeTitle = "title";

std::unique_ptr<Window> Window::Build(const Configuration& configuration) {
  const stl_string implementation = configuration.Get<stl_string>(
      kConfigModule, kConfigAttributeImplementation).first;
  if (implementation == GLFWWindow::kConfigImplementationName) {
    auto new_object = AllocateUniqueObject<GLFWWindow>();
    const auto width_config = configuration.Get<int>(
        kConfigModule, kConfigAttributeWidth);
    if (!width_config.second) {
      LOG(ERROR) << "Window width not found in config file.";
      return nullptr;
    }
    const auto height_config = configuration.Get<int>(
        kConfigModule, kConfigAttributeHeight);
    if (!height_config.second) {
      LOG(ERROR) << "Window height not found in config file.";
      return nullptr;
    }
    const auto opengl_major_version_config = configuration.Get<int>(
        kConfigModule, "opengl_major_version");
    const auto opengl_minor_version_config = configuration.Get<int>(
        kConfigModule, "opengl_minor_version");
    if (!opengl_major_version_config.second ||
        !opengl_minor_version_config.second) {
      LOG(ERROR)
          << "Window  opengl_major/minor_version not found in config file.";
      return nullptr;
    }
    const auto msaa_samples_config = configuration.Get<int>(
        kConfigModule, "msaa_samples");
    if (!msaa_samples_config.second) {
      LOG(ERROR) << "Window msaa_samples not found in config file.";
    }

    // Not important.
    const stl_string title = configuration.Get<stl_string>(
        kConfigModule, kConfigAttributeTitle).first;

    if (new_object->Create(width_config.first, height_config.first, title,
                           opengl_major_version_config.first,
                           opengl_minor_version_config.first,
                           msaa_samples_config.first)) {
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
