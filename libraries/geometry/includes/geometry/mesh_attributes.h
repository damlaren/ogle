/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines MeshAttributes.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_ATTRIBUTES_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_ATTRIBUTES_H_

#include <vector>
#include "math/vector.h"
#include "memory/buffer.h"

namespace ogle {

/**
 * @brief Wraps vectors containing mesh data.
 */
struct MeshAttributes {
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> tex_coords_uv;
  std::vector<Vector3f> tex_coords_uvw;
  std::vector<Vector3f> normals;
  std::vector<BufferIndex> vertex_indices;
  std::vector<BufferIndex> tex_coord_indices;
  std::vector<BufferIndex> normal_indices;
};

}  // namespace ogle

#endif // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_ATTRIBUTES_H_
