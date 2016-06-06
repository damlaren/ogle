/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of resource.h.
 */

#include "resource/resource.h"

namespace ogle {

const stl_string Resource::kIdField = "id";

const stl_string Resource::kTypeField = "type";

const stl_string Resource::kImplementationField = "implementation";

const stl_string Resource::kFilenameField = "filename";

const stl_string Resource::kDependenciesField = "dependencies";

const ResourceMetadata& Resource::metadata() const {
  return metadata_;
}

const ResourceID Resource::id() const {
  return metadata_.id();
}

const stl_string Resource::implementation() const {
  return metadata_.implementation();
}

const ResourceType Resource::type() const {
  return metadata_.type();
}

const stl_string Resource::subtype(const size_t level) const {
  return metadata_.subtype(level);
}

Resource::Resource(const ResourceMetadata& metadata)
  : metadata_(metadata) {
}

}  // namespace ogle
