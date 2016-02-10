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

#include <cstdint>
#include <string>
#include "geometry/buffer.h"
#include "math/vector.h"

namespace ogle {

/// 3D vertex buffer type.
using VertexBuffer = Buffer<Vector3f>;

/// Index buffer type.
using IndexBuffer = Buffer<std::int32_t>;

/// 3D normal vector buffer.
using NormalBuffer = Buffer<Vector3f>;

/// 2D texture coordinate buffer.
using TexCoordUVBuffer = Buffer<Vector2f>;

/// 3D texture coordinate buffer.
using TexCoordUVWBuffer = Buffer<Vector3f>;

/**
 * @brief A 3D geometry mesh.
 *
 * Meshes support 3D vertices and normals, and 2D texture buffers.
 * Meshes own the buffers they store and are responsible for deallocating them.
 */
class Mesh {
 public:
  // TODO(damlaren): Protect.
  /**
   * @brief Creates an empty Mesh.
   */
  Mesh(VertexBuffer&& vertex_buffer, NormalBuffer&& normal_buffer,  // NOLINT
       TexCoordUVBuffer&& uv_buffer, IndexBuffer&& vertex_index_buffer,  // NOLINT
       IndexBuffer&& normal_index_buffer, IndexBuffer&& tex_index_buffer);  // NOLINT

  /**
   * @brief Destructor.
   *
   * Deletes all buffers.
   */
  ~Mesh();

  /**
   * @brief Creates a new Mesh constructed from parsing a file.
   *
   * The caller takes ownership of the Mesh.
   *
   * @param file_path Path to file to load. Extension determines file format.
   * @return Pointer to new Mesh, or nullptr if creation failed.
   */
  static Mesh* LoadMesh(const std::string& file_path);

  /**
   * @brief Gives ownership of buffers to mesh.
   * @param vertices Vertex buffer. Invalid after call.
   */
  void TakeBuffers(VertexBuffer&& vertices);  // NOLINT

  /**
   * @brief Provides access to vertex buffer.
   * @return Reference to mesh vertices.
   */
  const VertexBuffer& vertices() const;

 protected:
  /// Vertex buffer.
  VertexBuffer vertices_;

  /// Vertex normals.
  NormalBuffer normals_;

  /// 2D texture buffer.
  TexCoordUVBuffer uvs_;

  // 3D texture buffers are not supported but could be added separately.

  //@{
  /// Index buffer for field.
  IndexBuffer vertex_indices_;
  IndexBuffer normal_indices_;
  IndexBuffer tex_coord_indices_;
  //@}
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
