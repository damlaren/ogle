/**
 * @file scene_graph.cc
 * @brief Implements scene_graph.h.
 */

#include "renderer/scene_graph.h"

namespace ogle {

SceneGraph::SceneGraph()
  : root_(AllocateUniqueObject<Entity>(nullptr)) {
}

}  // namespace ogle
