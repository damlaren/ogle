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
#include "file_system/file_path.h"
#include "input/glfw_keyboard_input.h"
#include "renderer/glfw_window.h"

namespace ogle {

Engine::Engine(const Configuration& configuration)
  : configuration_(configuration) {
}

bool Engine::Create() {
  resource_manager_ = AllocateUniqueObject<ogle::ResourceManager>();
  resource_manager_->AddResourceDirectory(
      FilePath(configuration_.Get<stl_string>("resource", "resource_dir")));

  window_ = Window::Build(configuration_);
  if (!window_) {
    LOG(ERROR) << "Failed to create window.";
    return false;
  }
  keyboard_ = KeyboardInput::Build(configuration_, window_.get());

  scene_graph_ = AllocateUniqueObject<ogle::SceneGraph>();
  scene_renderer_ = AllocateUniqueObject<ogle::SceneRenderer>();

  return true;
}

void Engine::Render(Entity* camera_entity) {
  window_->ClearWindow();
  scene_renderer_->RenderScene(camera_entity, scene_graph_.get());
  window_->SwapBuffers();
}

}  // namespace ogle
