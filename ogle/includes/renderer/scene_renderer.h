/**
 * @file scene_renderer.h
 * @brief Defines SceneRenderer.
 */

#ifndef OGLE_INCLUDES_RENDERER_SCENE_RENDERER_H_
#define OGLE_INCLUDES_RENDERER_SCENE_RENDERER_H_

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
   * @param camera_entity Entity containing Camera for rendering.
   * @param entity Entity to render.
   */
  virtual void Render(Entity* camera_entity, Entity* entity);

  /**
   * @brief Render entire scene.
   * @param camera_entity Entity containing Camera from which to render scene.
   * @param scene_graph Hierarchy of Entities to render.
   */
  virtual void RenderScene(Entity* camera_entity, SceneGraph* scene_graph);
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SCENE_RENDERER_H_
