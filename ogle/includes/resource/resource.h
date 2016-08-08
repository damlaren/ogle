/**
 * @file Defines Resource.
 */

#ifndef OGLE_INCLUDES_RESOURCE_RESOURCE_H_
#define OGLE_INCLUDES_RESOURCE_RESOURCE_H_

#include "std/ogle_std.inc"
#include <memory>
#include "resource/resource_metadata.h"

namespace ogle {

/**
 * @brief A static resource loaded from the file system.
 *
 * A Resource is distinguished by these traits:
 *
 * 1. Only one copy of it is needed in memory.
 * 2. It is an asset usually loaded from the file system.
 * 3. It doesn't change after being loaded.
 *
 * Each resource must have a globally unique ID loaded from metadata.
 * Each type inheriting from resource must also define a kResourceType constant
 * which takes on one of the values defined by ResourceType.
 */
class Resource {
 public:
  /// Field for globally unique resource ID.
  static const stl_string kIdField;

  /// Field identifying resource type.
  static const stl_string kTypeField;

  /// String separating resource subtypes.
  static constexpr char kTypeSeparator = '/';

  /// Field identifying implementation of resource to use.
  static const stl_string kImplementationField;

  /// Field identifying file basename of resource.
  static const stl_string kFilenameField;

  /// Field identifying dependencies of this resource.
  static const stl_string kDependenciesField;

  /**
   * @brief Destructor.
   */
  virtual ~Resource() = default;

  /**
   * @brief Accessor.
   * @return Metadata.
   */
  const ResourceMetadata& metadata() const;

  /**
   * @brief Accessor.
   * @return Unique ID of resource.
   */
  const ResourceID id() const;

  /**
   * @brief Accessor.
   * @return Implementation used for resource. May be empty.
   */
  const stl_string implementation() const;

  /**
   * @brief Accessor.
   * @return Type of resource.
   */
  const ResourceType type() const;

  /**
   * @brief Accessor.
   * @param level Level at which to get subtype.
   * @return Resource subtype. Empty string if not found.
   */
  const stl_string subtype(const size_t level) const;

 protected:
  /**
   * @brief Constructor.
   * @param metadata Resource metadata.
   */
  explicit Resource(const ResourceMetadata& metadata);

  /// Metadata describing resource.
  ResourceMetadata metadata_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RESOURCE_RESOURCE_H_
