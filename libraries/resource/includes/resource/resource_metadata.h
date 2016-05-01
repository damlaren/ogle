/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines ResourceMetadata.
 */

#ifndef LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_
#define LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_

#include "std/ogle_std.inc"
#include <iostream>
#include "easylogging++.h"  // NOLINT
#include "yaml-cpp/yaml.h"

namespace ogle {

class FilePath;

/// Type for ID of a resource.
using ResourceID = stl_string;

/**
 * @brief Metadata associated with each Resource.
 *
 * The metadata contains enough information to construct the resource.
 */
class ResourceMetadata {
 public:
  /**
   * @brief Loads metadata from file.
   * @param file_path Name of file from which to load metadata.
   * @return new ResourceMetadata object.
   */
  static ResourceMetadata Load(const FilePath& file_path);

  /**
   * @brief Output stream operator.
   * @param[in,out] os Output stream.
   * @param[in] metadata Object to print.
   * @return Reference to #os.
   */
  friend std::ostream& operator<<(std::ostream& os,  // NOLINT
                                  const ResourceMetadata& metadata);

  /**
   * @brief Accessor.
   * @return true if metadata was successfully loaded from file.
   */
  const bool loaded() const;

  /**
   * @brief Accessor.
   * @return Resource ID.
   */
  const ResourceID id() const;

  /**
   * @brief Gets value of attribute from metadata.
   *
   * @param attribute_name Name of attribute to look up.
   * @return Retrieved value, or default-constructed object if nothing.
   */
  template <typename T>
  const T Get(const stl_string& attribute_name) const {
    if (root_node_) {
      const auto& attribute_node = root_node_[attribute_name];
      if (attribute_node) {
        return attribute_node.as<T>();
      }
    }
    LOG(ERROR) << "Resource attribute not found: " << attribute_name;
    return T{};
  }

 private:
  /**
   * @brief Hidden constructor.
   * @param id Unique ID for Resource.
   */
  explicit ResourceMetadata(const ResourceID& id);

  /// Root of loaded YAML file.
  YAML::Node root_node_;

  /// Unique ID associated with Resource.
  ResourceID id_;
};

}  // namespace ogle

#endif  // LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_