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

void SceneRenderer::RenderScene(const Entity& camera_entity,
                                const stl_vector<const Entity*>& light_entities,
                                SceneGraph* scene_graph) {
  // This is the dumbest possible solution: just iterate through the entire
  // graph and draw objects in the order they are encountered.
  if (scene_graph->root_ == nullptr) {
    LOG(ERROR) << "Scene graph has no root.";
  } else if (camera_entity.GetComponent<Camera>() == nullptr) {
    LOG(ERROR) << "Camera Entity for RenderScene has no Camera attached.";
  } else {
    Render(camera_entity, light_entities, scene_graph->root_.get());
  }
}

void SceneRenderer::Render(const Entity& camera_entity,
                           const stl_vector<const Entity*>& light_entities,
                           Entity *entity) {
  Renderer* renderer = entity->GetComponent<Renderer>();
  if (renderer != nullptr) {
    renderer->Render(entity->transform_, camera_entity, light_entities);
  }
  for (Transform* child_transform : entity->transform_.children()) {
    Render(camera_entity, light_entities, child_transform->entity());
  }
}

}  // namespace ogle
