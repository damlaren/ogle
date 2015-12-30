/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Mesh class.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_

#include "geometry/buffer.h"
#include "math/vector.h"

namespace ogle {

/// Type for a 3D Vertex buffer.
using VertexBuffer = Buffer<ogle::Vector3f>;

/**
 * @brief 3D geometry mesh.
 * Takes ownership of its buffers.
 */
class Mesh {
 public:
  /**
   * @brief Creates an empty mesh.
   */
  Mesh();

  /**
   * @brief Destructor.
   *
   * Deletes all buffers.
   */
  ~Mesh();

  /**
   * @brief Gives ownership of buffers to mesh.
   * @param[in] vertices Vertex buffer. Invalid after call.
   */
  void StealBuffers(VertexBuffer&& vertices);  // NOLINT

  /**
   * @brief Provides access to vertex buffer.
   * @return Reference to mesh vertices.
   */
  const VertexBuffer& GetVertexBuffer() const;

 protected:
  /// Vertex buffer.
  VertexBuffer vertices_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
