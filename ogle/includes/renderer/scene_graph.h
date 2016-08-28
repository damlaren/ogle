/**
 * @file scene_graph.h
 * @brief Defines SceneGraph.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/entity.h"

namespace ogle {

/**
 * @brief Tracks all Entities in scene.
 *
 * It is assumed that the SceneGraph is a tree, with no cycles.
 */
class SceneGraph {
 public:
  /**
   * @brief Default Constructor.
   */
  SceneGraph();

  /// Entity at root of graph. All other Entities are beneath it.
  std::unique_ptr<Entity> root_;
};

}  // namespace ogle

