/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of mesh_loader.h.
 */

#include "geometry/mesh_loader.h"
#include <regex>  // NOLINT
#include <vector>
#include "easylogging++.h"  // NOLINT
#include "geometry/mesh.h"
#include "util/text_file.h"

namespace ogle {

Mesh* MeshLoader::LoadMesh(const std::string& file_path) {
  const MeshFileFormat mesh_format = DetermineMeshFormat(file_path);
  Mesh* new_mesh = nullptr;
  switch (mesh_format) {
    case MeshFileFormat::OBJ: {
      new_mesh = LoadOBJ(file_path);
      break;
    }
    case MeshFileFormat::UNKNOWN:  // Fall through.
    default: {
      LOG(ERROR) << "Unable to determine format of Mesh at: " << file_path;
      break;
    }
  }
  return new_mesh;
}

const MeshLoader::MeshFileFormat MeshLoader::DetermineMeshFormat(
    const std::string& file_path) {
  const std::string::size_type separatorIndex = file_path.find_last_of(".");
  if (separatorIndex != std::string::npos) {
    const std::string extension = file_path.substr(separatorIndex);
    if (extension == ".obj") {
      return MeshFileFormat::OBJ;
    }
  }
  return MeshFileFormat::UNKNOWN;
}

Mesh* MeshLoader::LoadOBJ(const std::string& file_path) {
  std::string text;
  if (!TextFile::ReadFile(file_path, &text)) {
    return nullptr;
  }

  std::vector<std::string> lines;
  TextFile::SplitLines(text, &lines);
  text.clear();

  return new Mesh();
}

}  // namespace ogle
