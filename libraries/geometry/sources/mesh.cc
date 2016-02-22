/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of mesh.h.
 */

#include "geometry/mesh.h"
#include "geometry/mesh_loader.h"
#include <string>

namespace ogle {

Mesh::Mesh(VertexBuffer&& vertex_buffer,  // NOLINT
           TexCoordUVBuffer&& uv_buffer,  // NOLINT
           NormalBuffer&& normal_buffer,  // NOLINT
           IndexBuffer&& index_buffer)  // NOLINT
  : vertices_(std::move(vertex_buffer)),
    uvs_(std::move(uv_buffer)),
    normals_(std::move(normal_buffer)),
    indices_(std::move(index_buffer)) {
}

Mesh* Mesh::LoadMesh(const std::string& file_path) {
  return MeshLoader::LoadMesh(file_path);
}

const VertexBuffer& Mesh::vertices() const {
  return vertices_;
}

const TexCoordUVBuffer& Mesh::uvs() const {
  return uvs_;
}

const NormalBuffer& Mesh::normals() const {
  return normals_;
}

const IndexBuffer& Mesh::indices() const {
  return indices_;
}

}  // namespace ogle
