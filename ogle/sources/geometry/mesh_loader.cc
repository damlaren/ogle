/**
 * @file Implementation of mesh_loader.h.
 */

#include "geometry/mesh_loader.h"
#include "easylogging++.h"  // NOLINT
#include "geometry/mesh.h"
#include "file_system/text_file.h"
#include "resource/resource_metadata.h"
#include "util/string_utils.h"

namespace ogle {

std::unique_ptr<Mesh> MeshLoader::LoadMesh(const ResourceMetadata& metadata) {
  if (metadata.type() != ResourceType::MESH) {
    LOG(ERROR) << "Attempted to load Mesh from incorrect metadata type: "
               << metadata.type();
    return nullptr;
  }

  const MeshFileFormat mesh_format = DetermineMeshFormat(metadata);

  switch (mesh_format) {
    case MeshFileFormat::OBJ: {
      return std::move(LoadOBJ(metadata));
    }

    case MeshFileFormat::UNKNOWN:  // Fall through.
    default: {
      LOG(ERROR) << "Unable to determine format of mesh from metadata: "
                 << metadata;
      break;
    }
  }

  LOG(ERROR) << "Failed to load Mesh.";
  return nullptr;
}

const MeshLoader::MeshFileFormat MeshLoader::DetermineMeshFormat(
    const ResourceMetadata& metadata) {
  const auto implementation = StringUtils::Lower(metadata.implementation());
  if (implementation == "obj") {
    return MeshFileFormat::OBJ;
  }
  return MeshFileFormat::UNKNOWN;
}

std::unique_ptr<Mesh> MeshLoader::LoadOBJ(const ResourceMetadata& metadata) {
  stl_string text;
  const auto& file_path = metadata.resource_path();
  if (!TextFile::ReadTextFile(file_path, &text)) {
    return nullptr;
  }
  stl_vector<stl_string> lines = StringUtils::Split(text, '\n');
  text.clear();

  auto mesh = AllocateUniqueObject<Mesh>(metadata);
  MeshAttributes mesh_data;
  for (const auto& line : lines) {
    stl_string trimmed_line = StringUtils::Trim(line, " \t\r\n");
    if (trimmed_line.empty() || trimmed_line[0] == '#') {
      continue;
    }
    trimmed_line = StringUtils::Replace(trimmed_line, '\t', ' ');
    const auto tokens = StringUtils::Split(trimmed_line, ' ');
    const stl_string& line_type = tokens[0];
    stl_vector<float> line_floats;

    if (line_type == "v") {
      for (stl_vector<stl_string>::size_type token_index = 1;
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
        return nullptr;
      }
      mesh_data.vertices.emplace_back(line_vector);
    } else if (line_type == "vt") {
      for (stl_vector<stl_string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        line_floats.emplace_back(std::stof(tokens[token_index]));
      }
      if (line_floats.size() == 2) {
        mesh_data.tex_coords_uv.emplace_back(
            Vector2f({line_floats[0], line_floats[1]}));
      } else if (line_floats.size() == 3) {
        mesh_data.tex_coords_uvw.emplace_back(
            Vector3f({line_floats[0], line_floats[1], line_floats[2]}));
      }
    } else if (line_type == "vn") {
      for (stl_vector<stl_string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        line_floats.emplace_back(std::stof(tokens[token_index]));
      }

      // This does not check if the normal vector is actually normalized--
      // it leaves this possibility open on purpose.
      mesh_data.normals.emplace_back(
          Vector3f({line_floats[0], line_floats[1], line_floats[2]}));
    } else if (line_type == "vp") {
      LOG(ERROR) << "LoadOBJ cannot load parameter space vertices.";
      return nullptr;
    } else if (line_type == "f") {
      // Several different formats are possible, split by '/'.
      if (tokens.size() != 4) {  // 'f' + 3 vertices.
        LOG(ERROR) << "Non-triangular faces are not supported.";
        return nullptr;
      }

      stl_vector<Vector3f> face_vertices;
      stl_vector<Vector2f> face_vertex_uvs;
      stl_vector<Vector3f> face_vertex_normals;
      for (stl_vector<stl_string>::size_type token_index = 1;
           token_index < tokens.size(); token_index++) {
        const stl_string& index_specifier = tokens[token_index];
        const auto first_slash_index = index_specifier.find_first_of('/');
        const auto last_slash_index = index_specifier.find_last_of('/');
        stl_string vertex_str = "", tex_str = "", normal_str = "";

        if (index_specifier.find("//") != stl_string::npos) {  // v//n
          vertex_str = index_specifier.substr(0, first_slash_index);
          normal_str = index_specifier.substr(last_slash_index + 1);
        } else if (first_slash_index != last_slash_index) {  // v/t/n
          vertex_str = index_specifier.substr(0, first_slash_index);
          tex_str = index_specifier.substr(
              first_slash_index + 1, last_slash_index - first_slash_index - 1);
          normal_str = index_specifier.substr(last_slash_index + 1);
        } else if (first_slash_index != stl_string::npos &&
                   first_slash_index == last_slash_index) {  // v/t
          vertex_str = index_specifier.substr(0, first_slash_index);
          tex_str = index_specifier.substr(first_slash_index + 1);
        } else {  // v
          vertex_str = index_specifier;
        }

        // OBJ indices start at 1, but memory indices start at 0. This function
        // handles the conversion; it is anonymized on the assumption that it is
        // only relevant inside the OBJ mesh loader.
        auto convert_obj_index = [](const stl_string& index_str) {
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
            return nullptr;
          }
          face_vertices.emplace_back(mesh_data.vertices[index]);
        }
        if (!tex_str.empty()) {
          const BufferIndex index = convert_obj_index(tex_str);
          if (index > mesh_data.tex_coords_uv.size()) {
            LOG(ERROR) << "Face UV not found for index: " << index;
            return nullptr;
          }
          face_vertex_uvs.emplace_back(mesh_data.tex_coords_uv[index]);
        }
        if (!normal_str.empty()) {
          const BufferIndex index = convert_obj_index(normal_str);
          if (index > mesh_data.normals.size()) {
            LOG(ERROR) << "Face normal not found for index: " << index;
            return nullptr;
          }
          face_vertex_normals.emplace_back(mesh_data.normals[index]);
        }
      }

      if (!mesh->AddFace(face_vertices, face_vertex_uvs, face_vertex_normals)) {
        LOG(ERROR) << "Failed to add mesh face.";
        return nullptr;
      }
    }
  }

  return mesh;
}

}  // namespace ogle
