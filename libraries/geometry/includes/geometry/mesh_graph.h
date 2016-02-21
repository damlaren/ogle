/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines MeshGraph.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_GRAPH_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_GRAPH_H_

#include "math/vector.h"

namespace ogle {

class MeshAttributes;

/**
 * @brief A mesh representation with face-vertex connectivity information.
 */
class MeshGraph {
 public:
    /**
     * @brief Mesh vertex, associated attributes, and face connections.
     */
    struct MeshVertex {
      Vector3f vertex;  ///< Vertex location.
      Vector2f uv;  ///< 2D texture coordinate.
      Vector3f vertex_normal;  ///< Vertex normal.

      /// Faces connected to this Vertex.
      std::vector<struct MeshFace*> adjoining_faces;

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
      Vector3f face_normal;  ///< Normal for this face.

      /// Vertices making up this face.
      std::vector<MeshVertex*> vertices;
    };

  /**
   * @brief Creates a graph.
   * @param mesh_data MeshAttributes to construct graph from.
   */
  bool Load(const MeshAttributes* mesh_data);
};

}  // namespace ogle

#endif // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_GRAPH_H_
