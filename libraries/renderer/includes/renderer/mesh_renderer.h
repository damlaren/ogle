/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines MeshRenderer.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_MESH_RENDERER_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_MESH_RENDERER_H_

#include <memory>
#include "renderer/renderer.h"

namespace ogle {

class Mesh;

/**
 * @brief Base class for all MeshRenderers.
 *
 * Subclasses handle different APIs.
 */
class MeshRenderer : public Renderer {
 public:
  /**
   * @brief Constructor.
   * @param mesh Mesh to render.
   */
  explicit MeshRenderer(const Mesh& mesh);

 protected:
  /// Mesh to render.
  const Mesh& mesh_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_MESH_RENDERER_H_
