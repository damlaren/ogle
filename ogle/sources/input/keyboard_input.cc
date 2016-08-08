/**
 * @file Implementation of keyboard_input.h.
 */

#include "input/keyboard_input.h"
#include "config/configuration.h"
#include "input/glfw_keyboard_input.h"
#include "window/glfw_window.h"
#include "window/window.h"

namespace ogle {

std::size_t KeyCodeHash::operator()(const KeyCode code) const {
  return std::hash<int>()(static_cast<int>(code));
}

const stl_string KeyboardInput::kConfigModule = "input";

const stl_string KeyboardInput::kConfigAttributeImplementation =
    "keyboard_implementation";

std::unique_ptr<KeyboardInput> KeyboardInput::Build(
    const Configuration& configuration, Window* window) {
  const stl_string implementation = configuration.Get<stl_string>(
      kConfigModule, kConfigAttributeImplementation).first;
  if (implementation == GLFWKeyboardInput::kConfigImplementationName) {
    auto new_object = AllocateUniqueObject<GLFWKeyboardInput>();

    // GLFW tangles its keyboard and window together.
    if (window != nullptr) {
      auto window_configuration = configuration.Get<stl_string>(
          Window::kConfigModule, Window::kConfigAttributeImplementation);
      if (window_configuration.first == GLFWWindow::kConfigImplementationName) {
        static_cast<GLFWWindow*>(window)->AttachKeyboard(new_object.get());
        return std::move(new_object);
      }
    } else {
      LOG(ERROR) << "Window must be provided to create GLFWKeyboardInput.";
    }
  }
  LOG(ERROR) << "Unable to create KeyboardInput for implementation: "
             << implementation;
  return nullptr;
}

const bool KeyboardInput::IsShiftDown(const bool repeat) {
  return IsKeyDown(KeyCode::LEFT_SHIFT, repeat) ||
         IsKeyDown(KeyCode::RIGHT_SHIFT, repeat);
}

}  // namespace ogle
