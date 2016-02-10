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

Mesh::Mesh(VertexBuffer&& vertex_buffer, NormalBuffer&& normal_buffer,  // NOLINT
           TexCoordUVBuffer&& uv_buffer, IndexBuffer&& vertex_index_buffer,  // NOLINT
           IndexBuffer&& normal_index_buffer, IndexBuffer&& tex_index_buffer)  // NOLINT
  : vertices_(std::move(vertex_buffer)), normals_(std::move(normal_buffer)),
    uvs_(std::move(uv_buffer)),
    vertex_indices_(std::move(vertex_index_buffer)),
    normal_indices_(std::move(normal_index_buffer)),
    tex_coord_indices_(std::move(tex_index_buffer)) {
}

Mesh::~Mesh() {
}

Mesh* Mesh::LoadMesh(const std::string& file_path) {
  return MeshLoader::LoadMesh(file_path);
}

void Mesh::TakeBuffers(VertexBuffer&& vertices) {  // NOLINT
  vertices_ = std::move(vertices);
}

const VertexBuffer& Mesh::vertices() const {
  return vertices_;
}

}  // namespace ogle
