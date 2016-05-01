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
#include "file_system/file_path.h"

namespace ogle {

ResourceMetadata::ResourceMetadata(const ResourceID& id)
  : id_(id) {
}

std::ostream& operator<<(std::ostream& os, const ResourceMetadata& metadata) {
  os << metadata.root_node_;
  return os;
}

ResourceMetadata ResourceMetadata::Load(const FilePath& file_path) {
  ResourceMetadata new_metadata(file_path.str());
  new_metadata.root_node_ = YAML::LoadFile(file_path.str());
  if (!new_metadata.root_node_) {
    LOG(ERROR) << "Failed to load resource metadata from: " << file_path.str();
  }
  return new_metadata;
}

const bool ResourceMetadata::loaded() const {
  return root_node_;
}

const ResourceID ResourceMetadata::id() const {
  return id_;
}

}  // namespace ogle