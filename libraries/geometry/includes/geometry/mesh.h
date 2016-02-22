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
#include "math/vector.h"
#include "memory/buffer.h"

namespace ogle {

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
 * @brief A 3D geometry mesh for rendering.
 *
 * All Meshes contain the following data. Formats are standardized to simplify
 * rendering code:
 * - 3D vertices (4D vertices parsed from files are homogenized on load)
 * - 3D normal vectors
 * - 2D UV texture coordinates
 * - Index buffers into all of the above
 *
 * Meshes only store buffers of raw data. They do not contain additional
 * structures typically used for querying relations between faces and vertex
 * attributes.
 *
 * Meshes own the buffers they store and are responsible for deallocating them.
 */
class Mesh {
 public:
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

  //@{
  /**
   * @brief Mesh data buffer accessors.
   * @return Reference to buffer.
   */
  const VertexBuffer& vertices() const;
  //@}

  //@{
  /**
   * @brief Index buffer accessors.
   * @return Reference to index buffer.
   */
  const IndexBuffer& vertex_indices() const;
  //@}

 protected:
  /// Vertex buffer.
  VertexBuffer vertices_;

  /// Vertex normals.
  NormalBuffer normals_;

  /// 2D texture coordinate buffer.
  TexCoordUVBuffer uvs_;

  //@{
  /// Index buffer for field.
  IndexBuffer vertex_indices_;
  IndexBuffer normal_indices_;
  IndexBuffer tex_coord_indices_;
  //@}
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
