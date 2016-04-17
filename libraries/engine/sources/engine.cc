/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of engine.h.
 */

#include "engine/engine.h"
#include "input/glfw_keyboard_input.h"
#include "renderer/glfw_window.h"

namespace ogle {

const stl_string Engine::kGLFWImpl = "glfw";

Engine::Engine(const Configuration& configuration)
  : configuration_(configuration) {
}

bool Engine::Create() {
  resource_manager_ = std::make_unique<ogle::ResourceManager>(
      configuration_.Get<stl_string>("resource", "resource_dir"));

  // TODO(damlaren): factories
  auto glfw_window = std::make_unique<GLFWWindow>();
  if (!glfw_window->Create(
           configuration_.Get<int>("window", "width"),
           configuration_.Get<int>("window", "height"),
           configuration_.Get<stl_string>("window", "title"),
           configuration_.Get<int>("window", "opengl_major_version"),
           configuration_.Get<int>("window", "opengl_minor_version"),
           configuration_.Get<int>("window", "msaa_samples"))) {
    LOG(ERROR) << "Failed to create window.";
    return false;
  }
  auto glfw_keyboard = std::make_unique<GLFWKeyboardInput>();

  // GLFW tangles its keyboard and window together.
  if (configuration_.Get<stl_string>("window",
                                     "implementation") == kGLFWImpl &&
      configuration_.Get<stl_string>("input", "implementation") == kGLFWImpl) {
    glfw_window->AttachKeyboard(glfw_keyboard.get());
  }
  window_ = std::move(glfw_window);
  keyboard_ = std::move(glfw_keyboard);

  scene_graph_ = std::make_unique<ogle::SceneGraph>();
  scene_renderer_ = std::make_unique<ogle::SceneRenderer>();

  return true;
}

void Engine::Render(Entity* camera_entity) {
  window_->ClearWindow();
  scene_renderer_->RenderScene(camera_entity, scene_graph_.get());
  window_->SwapBuffers();
}

}  // namespace ogle
