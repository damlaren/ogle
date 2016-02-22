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
#include "easylogging++.h"  // NOLINT
#include "geometry/mesh.h"
#include "geometry/mesh_graph.h"
#include "util/string_utils.h"
#include "util/text_file.h"

namespace ogle {

Mesh* MeshLoader::LoadMesh(const std::string& file_path) {
  const MeshFileFormat mesh_format = DetermineMeshFormat(file_path);
  MeshGraph mesh_graph;
  bool success = false;

  switch (mesh_format) {
    case MeshFileFormat::OBJ: {
      success = LoadOBJ(file_path, &mesh_graph);
      break;
    }
    case MeshFileFormat::UNKNOWN:  // Fall through.
    default: {
      LOG(ERROR) << "Unable to determine format of Mesh at: " << file_path;
      break;
    }
  }

  if (!success) {
    LOG(ERROR) << "Failed to load Mesh.";
    return nullptr;
  }

  return BuildMesh(mesh_graph);
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

const bool MeshLoader::LoadOBJ(const std::string& file_path,
                               MeshGraph *mesh_graph) {
  std::string text;
  if (!TextFile::ReadFile(file_path, &text)) {
    return false;
  }
  std::vector<std::string> lines = StringUtils::Split(text, '\n');
  text.clear();

  mesh_graph->Clear();

  MeshAttributes mesh_data;
  for (const auto& line : lines) {
    std::string trimmed_line = StringUtils::Trim(line, " \t\r\n");
    if (trimmed_line.empty() || trimmed_line[0] == '#') {
      continue;
    }
    trimmed_line = StringUtils::Replace(trimmed_line, '\t', ' ');
    const auto tokens = StringUtils::Split(trimmed_line, ' ');
    const std::string& line_type = tokens[0];
    std::vector<float> line_floats;

    if (line_type == "v") {
      for (std::vector<std::string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        line_floats.emplace_back(std::stof(tokens[token_index]));
      }
      Vector3f line_vector;
      if (line_floats.size() == 3) {
          line_vector = {line_floats[0], line_floats[1], line_floats[2]};
      } else if (line_floats.size() == 4) {
        // Have w coordinate, produce a 3-vector with w = 1.
        const float w = line_floats[3];
        line_vector = {line_floats[0] / w, line_floats[1] / w,
                       line_floats[2] / w};
      } else {
        LOG(ERROR) << "Expected 3 or 4 floats for vertex.";
        return false;
      }
      mesh_data.vertices.emplace_back(line_vector);
    } else if (line_type == "vt") {
      for (std::vector<std::string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        line_floats.emplace_back(std::stof(tokens[token_index]));
      }
      if (line_floats.size() == 2) {
        mesh_data.tex_coords_uv.emplace_back(Vector2f({line_floats[0],
                                                       line_floats[1]}));
      } else if (line_floats.size() == 3) {
        mesh_data.tex_coords_uvw.emplace_back(
            Vector3f({line_floats[0], line_floats[1], line_floats[2]}));
      }
    } else if (line_type == "vn") {
      for (std::vector<std::string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        line_floats.emplace_back(std::stof(tokens[token_index]));
      }

      // This does not check if the normal vector is actually normalized--
      // it leaves this possibility open on purpose.
      mesh_data.normals.emplace_back(Vector3f({line_floats[0], line_floats[1],
                                               line_floats[2]}));
    } else if (line_type == "vp") {
      LOG(ERROR) << "LoadOBJ cannot load parameter space vertices.";
      return false;
    } else if (line_type == "f") {
      // Several different formats are possible, split by '/'.
      if (tokens.size() != 3) {
        LOG(ERROR) << "Non-triangular faces are not supported.";
        return false;
      }

      std::vector<Vector3f> face_vertices;
      std::vector<Vector2f> face_vertex_uvs;
      std::vector<Vector3f> face_vertex_normals;
      for (std::vector<std::string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        const std::string& index_specifier = tokens[token_index];
        const auto first_slash_index = index_specifier.find_first_of('/');
        const auto last_slash_index = index_specifier.find_last_of('/');
        std::string vertex_str = "", tex_str = "", normal_str = "";

        if (index_specifier.find("//") != std::string::npos) {  // v//n
          vertex_str = index_specifier.substr(0, first_slash_index);
          normal_str = index_specifier.substr(last_slash_index + 1);
        } else if (first_slash_index != last_slash_index) {  // v/t/n
          vertex_str = index_specifier.substr(0, first_slash_index);
          tex_str = index_specifier.substr(first_slash_index + 1,
              last_slash_index - first_slash_index - 1);
          normal_str = index_specifier.substr(last_slash_index + 1);
        } else if (first_slash_index == last_slash_index) {  // v/t
          vertex_str = index_specifier.substr(0, first_slash_index);
          tex_str = index_specifier.substr(first_slash_index + 1);
        } else {  // v
          vertex_str = index_specifier;
        }

        // OBJ indices start at 1, but memory indices start at 0. This function
        // handles the conversion; it is anonymized on the assumption that it is
        // only relevant inside the OBJ mesh loader.
        auto convert_obj_index = [](const std::string& index_str) {
          int index = std::stoi(index_str);
          if (index == 0) {
            LOG(ERROR) << "Invalid 0 index parsed from OBJ file.";
          } else if (index < 0) {
            LOG(ERROR) << "Negative OBJ indices are not supported.";
          } else {
            --index;
          }
          return index;
        };

        if (!vertex_str.empty()) {
          const BufferIndex index = convert_obj_index(vertex_str);
          if (index > mesh_data.vertices.size()) {
            LOG(ERROR) << "Face vertex not found for index: " << index;
            return false;
          }
          face_vertices.emplace_back(mesh_data.vertices[index]);
        }
        if (!tex_str.empty()) {
          const BufferIndex index = convert_obj_index(tex_str);
          if (index > mesh_data.tex_coords_uv.size()) {
            LOG(ERROR) << "Face UV not found for index: " << index;
            return false;
          }
          face_vertex_uvs.emplace_back(mesh_data.tex_coords_uv[index]);
        }
        if (!normal_str.empty()) {
          const BufferIndex index = convert_obj_index(normal_str);
          if (index > mesh_data.normals.size()) {
            LOG(ERROR) << "Face normal not found for index: " << index;
            return false;
          }
          face_vertex_normals.emplace_back(mesh_data.normals[index]);
        }
      }

      if (!mesh_graph->AddFace(face_vertices, face_vertex_uvs,
                               face_vertex_normals)) {
        LOG(ERROR) << "Failed to add mesh face.";
        return false;
      }
    }
  }

  return true;
}

Mesh* MeshLoader::BuildMesh(const MeshGraph& mesh_graph) {
  VertexBuffer vertex_buffer;
  TexCoordUVBuffer uv_buffer;
  NormalBuffer normal_buffer;
    /*
     * // TODO(damlaren): This will be used again...
     *
    return new Mesh(
        std::move(VertexBuffer(mesh_data.vertices)),
        std::move(NormalBuffer(mesh_data.normals)),
        std::move(TexCoordUVBuffer(mesh_data.tex_coords_uv)),
        std::move(IndexBuffer(mesh_data.vertex_indices)),
        std::move(IndexBuffer(mesh_data.normal_indices)),
        std::move(IndexBuffer(mesh_data.tex_coord_indices))); */
  return nullptr;
}

}  // namespace ogle
