/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines SceneGraph.
 */

#ifndef OGLE_INCLUDES_RENDERER_SCENE_GRAPH_H_
#define OGLE_INCLUDES_RENDERER_SCENE_GRAPH_H_

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

#endif  // OGLE_INCLUDES_RENDERER_SCENE_GRAPH_H_
