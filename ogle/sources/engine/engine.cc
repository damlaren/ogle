/**
 * @file engine.cc
 * @brief Implementation of engine.h.
 */

#include "engine/engine.h"
#include "file_system/file_path.h"
#include "input/glfw_keyboard_input.h"
#include "window/glfw_window.h"

namespace ogle {

Engine::Engine(const Configuration& configuration)
  : configuration_(configuration) {
}

bool Engine::Create() {
  resource_manager_ = AllocateUniqueObject<ogle::ResourceManager>();
  auto resource_dir_config = configuration_.Get<stl_string>(
      "resource", "resource_dir");
  if (!resource_dir_config.second) {
    LOG(ERROR) << "resource_dir not found in config file.";
    return false;
  }
  resource_manager_->AddResourceDirectory(FilePath(resource_dir_config.first));

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

void Engine::Render(const Entity& camera_entity,
                    const stl_vector<const Entity*> light_entities) {
  window_->ClearWindow();
  scene_renderer_->RenderScene(camera_entity, light_entities,
                               scene_graph_.get());
  window_->SwapBuffers();
}

}  // namespace ogle
