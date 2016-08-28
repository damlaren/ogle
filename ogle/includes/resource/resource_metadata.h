/**
 * @file resource_metadata.h
 * @brief Defines ResourceMetadata.
 */

#pragma once

#include "std/ogle_std.inc"
#include <iostream>
#include <utility>
#include "easylogging++.h"  // NOLINT
#include "file_system/file_path.h"
#include "file_system/yaml_file.h"
#include "resource/resource_type.h"

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
   * @brief Default constructor.
   */
  ResourceMetadata() = default;

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
   * @return Other resources this resource depends on.
   */
  const stl_vector<ResourceID> dependencies() const;

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
   * @return Pair with: (1) Retrieved value, or default-constructed object if
   *         nothing; and (2) flag indicating whether attribute was found.
   */
  template <typename T>
  const std::pair<T, bool> Get(const stl_string& attribute_name) const {
    return yaml_file_.Get<T>({attribute_name});
  }

 private:
  /// Parsed YAML file with resource data.
  YAMLFile yaml_file_;

  /// Path to resource on file system.
  FilePath resource_path_;

  /// Type of resource.
  ResourceType type_;
};

}  // namespace ogle

