/**
 * @file property.h
 * @brief Defines Property.
 */

#pragma once

#include "std/ogle_std.inc"
#include <type_traits>
#include "memory/buffer.h"

namespace ogle {

/// Type of each dimension.
using PropertyDimIndex = std::uint32_t;

/// Types which can be stored in properties.
enum class PropertyType {
  BOOLEAN,  // Boolean value.
  FLOAT,  // 32-bit float.
  DOUBLE,  // 64-bit float.
  STRING,  // Text string.
  UNKNOWN  // Unknown type (default).
};

/**
 * @brief Output stream operator for PropertyType.
 */
std::ostream& operator<<(std::ostream& os, const PropertyType type);

/**
 * @brief Describes a variable that can be set for an object.
 */
class Property {
 public:
  /**
   * @brief Constructor.
   * @param name Name of property.
   * @param dims Dimensions.
   */
  Property(const stl_string& name, const stl_vector<PropertyDimIndex>& dims);

  /**
   * @brief Returns true if this is a single value (0-dimensional).
   */
  const bool IsSingle() const;

  /**
   * @brief Returns true if this is a vector value (1-dim, length N).
   */
  const bool IsVector() const;

  /**
   * @brief Returns true if this is a matrix value (2-dim, size M x N).
   */
  const bool IsMatrix() const;

  /**
   * @brief Number of values stored by this property.
   */
  const PropertyDimIndex NumValues() const;

  /**
   * @brief Returns true if this is a numeric value.
   *
   * Bools are not considered numeric.
   */
  virtual const bool IsNumeric() const = 0;

  /**
   * @brief Returns generic pointer to raw data.
   */
  virtual const void* data() const = 0;

  /**
   * @brief Returns type of field stored.
   */
  virtual const PropertyType Type() const = 0;

  /**
   * @brief Returns property name.
   */
  const stl_string& name() const;

  /**
   * @brief Sets property name.
   */
  void set_name(const stl_string& name);

  /**
   * @brief Returns property dimensions.
   */
  const stl_vector<PropertyDimIndex> dims() const;

  /**
   * @brief Returns a copy of this property.
   */
  virtual std::unique_ptr<Property> Clone() const = 0;

 protected:
  stl_string name_;                    ///< Name of variable.
  stl_vector<PropertyDimIndex> dims_;  ///< Dimensions of variable.
};

template <typename T>
class PropertyInstance : public Property {
 public:
  /**
   * @brief Constructor.
   * @param name Property name.
   * @param dims Dimensions.
   * @param data Data to copy into property storage. Number of elements must
   *     match space specified by dims field.
   */
  PropertyInstance(const stl_string& name,
                   const stl_vector<PropertyDimIndex>& dims, const T* data)
    : Property(name, dims) {
    const auto num = NumValues();
    T* data_buf = AllocateBuffer<T>(num);
    for (PropertyDimIndex i = 0; i < num; i++) {
      data_buf[i] = data[i];
    }
    data_ = Buffer<T>(data_buf, num);
  }

  const bool IsNumeric() const override {
    return std::is_arithmetic<T>::value;
  }

  const void* data() const override {
    return static_cast<const void*>(data_.data());
  }

  const PropertyType Type() const override {
    return PropertyType::UNKNOWN;
  }

  std::unique_ptr<Property> Clone() const override {
    return AllocateUniqueObject<PropertyInstance<T>>(
        name_, dims_, data_.data());
  }

 private:
  /// Property data storage.
  Buffer<T> data_;
};

template<>
inline const PropertyType PropertyInstance<bool>::Type() const {
  return PropertyType::BOOLEAN;
}

template<>
inline const PropertyType PropertyInstance<float>::Type() const {
  return PropertyType::FLOAT;
}

template<>
inline const PropertyType PropertyInstance<double>::Type() const {
  return PropertyType::DOUBLE;
}

template<>
inline const PropertyType PropertyInstance<stl_string>::Type() const {
  return PropertyType::STRING;
}

}  // namespace ogle
