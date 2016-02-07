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
#include <string>
#include <vector>
#include "util/text_file.h"

namespace ogle {

Mesh::Mesh() :
    vertices_(VertexBuffer()), indices_(IndexBuffer()),
    normals_(NormalBuffer()), uvs_(TexCoordUVBuffer()) {
}

Mesh::~Mesh() {
}

Mesh* Mesh::LoadMesh(const std::string& file_path) {
  std::string text;
  if (!TextFile::ReadFile(file_path, &text)) {
    return nullptr;
  }

  std::vector<std::string> lines;
  TextFile::SplitLines(text, &lines);
  text.clear();

  // TODO(damlaren): fill this in.

  return new Mesh();
}

void Mesh::TakeBuffers(VertexBuffer&& vertices) {  // NOLINT
  vertices_ = std::move(vertices);
}

const VertexBuffer& Mesh::vertices() const {
  return vertices_;
}

}  // namespace ogle
