/**
 * @file resource.cc
 * @brief Implementation of resource.h.
 */

#include "resource/resource.h"

namespace ogle {

const stl_string Resource::kIdField = "id";

const stl_string Resource::kTypeField = "type";

const stl_string Resource::kImplementationField = "implementation";

const stl_string Resource::kFilenameField = "filename";

const stl_string Resource::kDependenciesField = "dependencies";

const ResourceMetadata& Resource::metadata() const { return metadata_; }

const ResourceID Resource::id() const { return metadata_.id(); }

const stl_string Resource::implementation() const {
  return metadata_.implementation();
}

const ResourceType Resource::type() const { return metadata_.type(); }

const stl_string Resource::subtype(const size_t level) const {
  return metadata_.subtype(level);
}

Resource::Resource(const ResourceMetadata& metadata) : metadata_(metadata) {}

}  // namespace ogle
