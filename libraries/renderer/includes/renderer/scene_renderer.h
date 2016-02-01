/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines SceneRenderer.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_SCENE_RENDERER_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_SCENE_RENDERER_H_

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
  virtual void Render(const Entity& camera_entity, Entity* entity);

  /**
   * @brief Render entire scene.
   * @param camera_entity Entity containing Camera from which to render scene.
   * @param scene_graph Hierarchy of Entities to render.
   */
  virtual void RenderScene(const Entity& camera_entity,
                           SceneGraph* scene_graph);
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_SCENE_RENDERER_H_
