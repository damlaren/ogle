/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Mesh.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_

#include <map>
#include <vector>
#include "math/vector.h"
#include "memory/buffer.h"

namespace ogle {

/**
 * @brief A mesh representation with face-vertex connectivity information.
 *
 * Meshes contain detailed information about the Mesh suitable for high-level
 * operations and algorithms. They are prepared for use on a rendering device by
 * constructing a BufferedMesh.
 */
class Mesh {
 public:
  struct MeshFace;

  /**
   * @brief Mesh vertex, associated attributes, and face connections.
   *
   * Vertices are ordered in a set. After storage their attributes should not
   * be changed, with the exception of face adjacency information.
   */
  struct MeshVertex {
    Vector3f vertex;  ///< Vertex location.
    Vector2f uv;  ///< 2D texture coordinate.
    Vector3f vertex_normal;  ///< Vertex normal.

    /// Faces connected to this Vertex. Can be altered without affecting
    /// container order.
    mutable std::vector<const MeshFace*> adjoining_faces;

    /**
     * @brief Less than operator. Compares vertex attributes in order.
     * @param lhs Left operand.
     * @param rhs Right operand.
     * @return true if lhs < rhs.
     */
    friend const bool operator<(const MeshVertex& lhs, const MeshVertex& rhs);
  };

  /**
   * @brief A single face of a Mesh.
   */
  struct MeshFace {
    /// Vertices making up this face.
    std::vector<const MeshVertex*> vertices;
  };

  /// Number of vertices per face. Only triangles are stored.
  static constexpr int kVerticesPerFace = 3;

  /**
   * @brief Adds a new face to this Mesh.
   *
   * An empty argument is ignored; the corresponding vertex attribute is zeroed
   * out. All non-empty vectors passed to this function must be of equal
   * length.
   *
   * @param vertices Face vertices.
   * @param uvs 2D texture coordinates.
   * @param vertex_normals Normals for each vertex.
   * @return true if adding face succeeded, false on error.
   */
  const bool AddFace(const std::vector<Vector3f>& vertices,
                     const std::vector<Vector2f>& uvs,
                     const std::vector<Vector3f>& vertex_normals);

  /**
   * @brief Clears all mesh representation data.
   */
  void Clear();

  /**
   * @brief Accessor.
   * @return Mapping of unique mesh vertices to indices.
   */
  const std::map<MeshVertex, BufferIndex>& mesh_vertices() const;

  /**
   * @brief Accessor.
   * @return Vector of triangle faces making up Mesh.
   */
  const std::vector<MeshFace>& mesh_faces() const;

 private:
  /// Unique mesh vertices, mapped to indices in insertion order.
  std::map<MeshVertex, BufferIndex> mesh_vertices_;

  /// Mesh faces.
  std::vector<MeshFace> mesh_faces_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_H_
