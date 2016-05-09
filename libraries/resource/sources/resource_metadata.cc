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
#include "resource/resource.h"

namespace ogle {

const stl_string ResourceMetadata::kFileExtension = "meta";

std::ostream& operator<<(std::ostream& os, const ResourceMetadata& metadata) {
  os << "Resource path: " << metadata.resource_path_ << std::endl
     << metadata.root_node_;
  return os;
}

ResourceMetadata ResourceMetadata::Load(const FilePath& file_path) {
  ResourceMetadata new_metadata;
  new_metadata.root_node_ = YAML::LoadFile(file_path.str());
  if (!new_metadata.root_node_) {
    LOG(ERROR) << "Failed to load resource metadata from: " << file_path.str();
  }

  // Set path to resource.
  const auto dirname = file_path.Dirname();
  if (!new_metadata.root_node_[Resource::kFilenameField]) {
    LOG(ERROR) << "Failed to identify path name of resource from metadata: "
               << file_path.str();
  } else {
    new_metadata.resource_path_ =
        dirname + FilePath(
            new_metadata.root_node_[Resource::kFilenameField].as<stl_string>());
  }

  return new_metadata;
}

const bool ResourceMetadata::loaded() const {
  return root_node_;
}

const ResourceID& ResourceMetadata::id() const {
  return resource_path_.str();
}

const FilePath& ResourceMetadata::resource_path() const {
  return resource_path_;
}

}  // namespace ogle
