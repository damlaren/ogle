/**
 * @file resource_metadata.cc
 * @brief Implementation of resource_metadata.h.
 */

#include "resource/resource_metadata.h"
#include <type_traits>
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
  new_metadata.type_ = ResourceType::UNKNOWN;
  for (ResourceType type = ResourceType::BEGIN; type != ResourceType::END;
       type = static_cast<ResourceType>(
           std::underlying_type<ResourceType>::type(type) + 1)) {
    std::stringstream ss;
    ss << type;
    if (type_string == ss.str()) {
      new_metadata.type_ = type;
      break;
    }
  }
  if (new_metadata.type_ == ResourceType::UNKNOWN) {
    LOG(ERROR) << "Couldn't identify resource type: " << type_string;
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

const ResourceType ResourceMetadata::type() const { return type_; }

const stl_string ResourceMetadata::subtype(const size_t level) const {
  const auto split_type = StringUtils::Split(
      Get<stl_string>(Resource::kTypeField).first, Resource::kTypeSeparator);
  if (split_type.size() <= level) {
    return "";
  }
  return split_type[level];
}

}  // namespace ogle
