/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines ResourceMetadata.
 */

#ifndef OGLE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_
#define OGLE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_

#include "std/ogle_std.inc"
#include <iostream>
#include <utility>
#include "easylogging++.h"  // NOLINT
#include "file_system/file_path.h"
#include "file_system/yaml_file.h"

namespace ogle {

class FilePath;

/// Type for ID of a resource.
using ResourceID = stl_string;

/// Supported resource types.
enum class ResourceType {
  MESH,
  SHADER,
  SHADER_PROGRAM,
  UNKNOWN
};

/**
 * @brief Metadata associated with each Resource.
 *
 * The metadata contains enough information to construct the resource.
 */
class ResourceMetadata {
 public:
  /// File extension expected for metadata files.
  static const stl_string kFileExtension;

  /**
   * @brief Loads metadata from file.
   * @param file_path Name of file from which to load metadata.
   * @return Pair containing: (1) new metadata, and
   *         (2) whether it was loaded successfully.
   */
  static std::pair<ResourceMetadata, bool> Load(const FilePath& file_path);

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
   * @return Unique ID associated with Resource.
   */
  const ResourceID id() const;

  /**
   * @brief Accessor.
   * @return Path to resource on file system.
   */
  const FilePath& resource_path() const;

  /**
   * @brief Accessor.
   * @return Implementation used for resource. May be empty.
   */
  const stl_string implementation() const;

  /**
   * @brief Accessor.
   * @return Resource type.
   */
  const ResourceType type() const;

  /**
   * @brief Accessor
   * @param level Type sublevel.
   * @return Subtype at level. Empty string if not found.
   */
  const stl_string subtype(const size_t level) const;

  /**
   * @brief Gets value of attribute from metadata.
   *
   * @param attribute_name Name of attribute to look up.
   * @return Retrieved value, or default-constructed object if nothing.
   */
  template <typename T>
  const T Get(const stl_string& attribute_name) const {
    return yaml_file_.Get<T>({attribute_name});
  }

 private:
  /**
   * @brief Hidden constructor.
   */
  ResourceMetadata() = default;

  /// Parsed YAML file with resource data.
  YAMLFile yaml_file_;

  /// Path to resource on file system.
  FilePath resource_path_;

  /// Type of resource.
  ResourceType type_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RESOURCE_RESOURCE_METADATA_H_
