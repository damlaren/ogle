/**
 * @file scene_renderer.h
 * @brief Defines SceneRenderer.
 */

#pragma once

#include "std/ogle_std.inc"

namespace ogle {

class Entity;
class SceneGraph;

class SceneRenderer {
 public:
  /**
   * @brief Default constructor.
   */
  SceneRenderer() = default;

  /**
   * @brief Destructor.
   */
  virtual ~SceneRenderer() = default;

  /**
   * @brief Render a specific Entity in graph.
   * @param camera_entity Entity containing camera for rendering.
   * @param light_entities Entities containing lights for scene.
   * @param entity Entity to render.
   */
  virtual void Render(const Entity& camera_entity,
                      const stl_vector<const Entity*>& light_entities,
                      Entity* entity);

  /**
   * @brief Render entire scene.
   * @param camera_entity Entity containing camera from which to render scene.
   * @param light_entities Entities containing lights for scene.
   * @param scene_graph Hierarchy of Entities to render.
   */
  virtual void RenderScene(const Entity& camera_entity,
                           const stl_vector<const Entity*>& light_entities,
                           SceneGraph* scene_graph);
};

}  // namespace ogle

