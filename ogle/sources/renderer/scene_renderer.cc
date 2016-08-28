/**
 * @file scene_renderer.cc
 * @brief Implements scene_renderer.h.
 */

#include "renderer/scene_renderer.h"
#include "easylogging++.h"  // NOLINT
#include "entity/entity.h"
#include "renderer/camera.h"
#include "renderer/renderer.h"
#include "renderer/scene_graph.h"

namespace ogle {

void SceneRenderer::RenderScene(Entity* camera_entity,
                                SceneGraph* scene_graph) {
  if (camera_entity == nullptr) {
    LOG(ERROR) << "Cannot render from null Camera Entity.";
    return;
  }

  // This is the dumbest possible solution: just iterate through the entire
  // graph and draw objects in the order they are encountered.
  if (scene_graph->root_ == nullptr) {
    LOG(ERROR) << "Scene graph has no root.";
  } else if (camera_entity->GetComponent<Camera>() == nullptr) {
    LOG(ERROR) << "Camera Entity for RenderScene has no Camera attached.";
  } else {
    Render(camera_entity, scene_graph->root_.get());
  }
}

void SceneRenderer::Render(Entity* camera_entity, Entity *entity) {
  if (entity == nullptr) {
    return;
  }

  Renderer* renderer = entity->GetComponent<Renderer>();
  if (renderer != nullptr) {
    renderer->Render(entity->transform_, camera_entity);
  }
  for (Transform* child_transform : entity->transform_.children()) {
    Render(camera_entity, child_transform->entity());
  }
}

}  // namespace ogle
