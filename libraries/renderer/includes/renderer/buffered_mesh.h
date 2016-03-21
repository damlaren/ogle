/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines BufferedMesh.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_BUFFERED_MESH_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_BUFFERED_MESH_H_

#include "std/ogle_std.inc"
#include "math/vector.h"
#include "memory/buffer.h"

namespace ogle {

class Mesh;

/// 3D vertex buffer type.
using VertexBuffer = Buffer<Vector3f>;

/// 2D texture coordinate buffer.
using TexCoordUVBuffer = Buffer<Vector2f>;

/// 3D texture coordinate buffer.
using TexCoordUVWBuffer = Buffer<Vector3f>;

/// 3D normal vector buffer.
using NormalBuffer = Buffer<Vector3f>;

/// Index buffer type.
using IndexBuffer = Buffer<std::uint32_t>;

/**
 * @brief A 3D geometry mesh that has been prepared for rendering.
 *
 * It is subclassed to implement meshes that are ready to be rendered by
 * specific graphics APIs and hardware. It is meant to prepare raw data buffers,
 * not to provide more functionality for the Mesh.
 */
class BufferedMesh {
 public:
  /**
   * @brief Constructor.
   * @param mesh Const reference to mesh to prepare for rendering.
   */
  explicit BufferedMesh(const Mesh& mesh);

  /**
   * @brief Destructor.
   */
  virtual ~BufferedMesh() = default;

  /**
   * @brief Prepares buffers for rendering the Mesh.
   * @return success or failure.
   */
  virtual bool Prepare() = 0;

 protected:
  /// Reference to Mesh to prepare buffers for.
  const Mesh& mesh_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_BUFFERED_MESH_H_
