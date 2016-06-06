/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of resource_metadata.h.
 */

#include "resource/resource_metadata.h"
#include "geometry/mesh.h"
#include "renderer/shader.h"
#include "resource/resource.h"
#include "util/string_utils.h"

namespace ogle {

const stl_string ResourceMetadata::kFileExtension = "meta";

std::ostream& operator<<(std::ostream& os, const ResourceMetadata& metadata) {
  os << "Resource path: " << metadata.resource_path_ << std::endl
     << metadata.yaml_file_;
  return os;
}

std::pair<ResourceMetadata, bool> ResourceMetadata::Load(
    const FilePath& file_path) {
  ResourceMetadata new_metadata;

  if (!new_metadata.yaml_file_.Load(file_path)) {
    return {new_metadata, false};
  }

  if (new_metadata.Get<stl_string>(Resource::kIdField).first.empty()) {
    LOG(ERROR) << "Metadata must have an ID.";
    return {new_metadata, false};
  }

  if (new_metadata.Get<stl_string>(Resource::kTypeField).first.empty()) {
    LOG(ERROR) << "Metadata must have a type.";
    return {new_metadata, false};
  }

  // Set path to resource.
  const auto dirname = file_path.Dirname();
  const auto resource_filename =
      new_metadata.Get<stl_string>(Resource::kFilenameField).first;
  if (resource_filename.empty()) {
    LOG(ERROR) << "Failed to identify path name of resource from metadata: "
               << file_path.str();
    return {new_metadata, false};
  } else {
    new_metadata.resource_path_ = dirname + FilePath(resource_filename);
  }

  // Set type.
  const auto type_string = new_metadata.subtype(0);
  if (type_string == Shader::kResourceType) {
    new_metadata.type_ = ResourceType::SHADER;
  } else if (type_string == ShaderProgram::kResourceType) {
    new_metadata.type_ = ResourceType::SHADER_PROGRAM;
  } else if (type_string == Mesh::kResourceType) {
    new_metadata.type_ = ResourceType::MESH;
  } else {
    new_metadata.type_ = ResourceType::UNKNOWN;
  }

  return {new_metadata, true};
}

const ResourceID ResourceMetadata::id() const {
  return Get<ResourceID>(Resource::kIdField).first;
}

const FilePath& ResourceMetadata::resource_path() const {
  return resource_path_;
}

const stl_string ResourceMetadata::implementation() const {
  return Get<stl_string>(Resource::kImplementationField).first;
}

const stl_vector<ResourceID> ResourceMetadata::dependencies() const {
  return Get<stl_vector<ResourceID>>(Resource::kDependenciesField).first;
}

const ResourceType ResourceMetadata::type() const {
  return type_;
}

const stl_string ResourceMetadata::subtype(const size_t level) const {
  const auto split_type = StringUtils::Split(
      Get<stl_string>(Resource::kTypeField).first, Resource::kTypeSeparator);
  if (split_type.size() <= level) {
    return "";
  }
  return split_type[level];
}

}  // namespace ogle
