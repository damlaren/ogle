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
 * @brief A 3D geometry mesh containing raw buffers for rendering.
 *
 * All Meshes contain the following data. Formats are standardized to simplify
 * rendering code:
 * - 3D vertices (4D vertices parsed from files are homogenized on load)
 * - 3D normal vectors
 * - 2D UV texture coordinates
 * - Index buffer that indexes all of the above at once.
 *
 * Meshes only store raw data buffers. They do not store information on the
 * relations between faces and vertices. The #MeshGraph class exists to work
 * with that kind of information.
 *
 * Meshes own the buffers they store and are responsible for deallocating them.
 */
class Mesh {
 public:
  /**
   * @brief Creates a Mesh using passed buffers.
   * @param vertex_buffer Vertex buffer.
   * @param uv_buffer 2D texture coordinate buffer.
   * @param normal_buffer Normal buffer.
   * @param index_buffer Index buffer.
   */
  Mesh(VertexBuffer&& vertex_buffer, TexCoordUVBuffer&& uv_buffer,  // NOLINT
       NormalBuffer&& normal_buffer, IndexBuffer&& index_buffer);  // NOLINT

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
  const TexCoordUVBuffer& uvs() const;
  const NormalBuffer& normals() const;
  const IndexBuffer& indices() const;
  //@}

 protected:
  /// Vertex buffer.
  VertexBuffer vertices_;

  /// 2D texture coordinate buffer.
  TexCoordUVBuffer uvs_;

  /// Vertex normals.
  NormalBuffer normals_;

  /// Index buffer.
  IndexBuffer indices_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
