/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements scene_renderer.h.
 */

#include "renderer/scene_renderer.h"
#include "easylogging++.h"  // NOLINT
#include "entity/entity.h"
#include "renderer/renderer.h"
#include "renderer/scene_graph.h"

namespace ogle {

void SceneRenderer::RenderScene(Entity* camera_entity,
                                SceneGraph* scene_graph) {
  // This is the dumbest possible solution: just iterate through the entire
  // graph and draw objects in the order they are encountered.
  CHECK(scene_graph->root_ != nullptr) << "Scene graph has no root.";
  CHECK(camera_entity->camera() != nullptr)
      << "Camera Entity for RenderScene has no Camera attached.";
  Render(camera_entity, scene_graph->root_.get());
}

void SceneRenderer::Render(Entity* camera_entity, Entity *entity) {
  Renderer* renderer = entity->renderer();
  if (renderer != nullptr) {
    renderer->Render(entity->transform_, camera_entity);
  }
  for (Transform* child_transform : entity->transform_.children()) {
    Render(camera_entity, child_transform->entity());
  }
}

}  // namespace ogle
