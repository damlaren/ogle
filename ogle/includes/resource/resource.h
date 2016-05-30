/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
