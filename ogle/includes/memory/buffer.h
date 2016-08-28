/**
 * @file buffer.h
 * @brief Defines Buffer.
 */

#ifndef OGLE_INCLUDES_MEMORY_BUFFER_H_
#define OGLE_INCLUDES_MEMORY_BUFFER_H_

#include "std/ogle_std.inc"
#include <algorithm>
#include <iterator>
#include "easylogging++.h"  // NOLINT

namespace ogle {

/// Type for indexing into a Buffer.
using BufferIndex = std::uint32_t;

/**
 * @brief Memory buffer class that cleans up after itself.
 */
template<typename T>
class Buffer {
 public:
  /**
   * @brief Constructor. Creates a buffer of requested size.
   *
   * Doesn't initialize values in buffer.
   *
   * @param num_elements How many elements to reserve.
   */
  explicit Buffer(BufferIndex num_elements = 0)
    : num_elements_(num_elements) {
    data_ = AllocateBuffer<T>(num_elements_);
  }

  /**
   * @brief Constructor. Creates a buffer from initializer list.
   * @param init_list Initial elements to copy.
   */
  Buffer(std::initializer_list<T> init_list)
    : num_elements_(init_list.size()) {
    data_ = AllocateBuffer<T>(num_elements_);
    if (num_elements_ > 0) {
      std::copy(std::begin(init_list), std::end(init_list), data_);
    }
  }

  /**
   * @brief Constructor. Creates a buffer that wraps existing array.
   * @param data Array that is taken as Buffer storage. The Buffer takes
   *        ownership of this memory. Cannot be null.
   * @param num_elements How many elements are in array.
   */
  Buffer(T* data, BufferIndex num_elements)
    : num_elements_(num_elements),
      data_(data) {
    CHECK(data_ != nullptr) << "Cannot create Buffer from null data.";
  }

  /**
   * @brief Constructor that copies data from a stl_vector.
   * @param data_vector Vector to copy.
   */
  explicit Buffer(const stl_vector<T>& data_vector)
    : num_elements_(data_vector.size()) {
    data_ = AllocateBuffer<T>(num_elements_);
    if (num_elements_ > 0) {
      std::copy(std::begin(data_vector), std::end(data_vector), data_);
    }
  }

  /**
   * @brief Copy constructor.
   * @param other Buffer to copy contents from. Shallow.
   */
  Buffer(const Buffer& other)
    : num_elements_(other.num_elements_) {
    data_ = AllocateBuffer<T>(num_elements_);
    if (num_elements_ > 0) {
      std::copy_n(std::begin(other.data_), num_elements_, data_);
    }
  }

  /**
   * @brief Move constructor.
   * @param other Buffer to take data from. Invalid afterwards.
   */
  Buffer(Buffer&& other)  // NOLINT
    : num_elements_(other.num_elements_) {
    data_ = other.data_;
    other.data_ = nullptr;
    other.num_elements_ = 0;
  }

  /**
   * @brief Destructor. Deletes data held by buffer.
   */
  ~Buffer() {
    if (data_ != nullptr) {
      delete[] data_;
    }
  }

  /**
   * @brief Copy assignment operator.
   *
   * Deletes existing data held by this Buffer, if a different amount of
   * space is required to hold the new contents.
   *
   * @param other Buffer to copy contents from. Shallow.
   * @return Reference to this Buffer.
   */
  Buffer& operator=(const Buffer& other) {
    if (num_elements_ != other.num_elements_) {
      delete[] data_;
      num_elements_ = other.num_elements_;
      data_ = AllocateBuffer<T>(num_elements_);
    }
    if (num_elements_ > 0) {
      CHECK(data_ != nullptr) << "Cannot copy to null data in Buffer.";
      std::copy_n(std::begin(other.data_), num_elements_, data_);
    }
    return *this;
  }

  /**
   * @brief Move assignment operator.
   *
   * Deletes existing data held by this Buffer.
   *
   * @param other Buffer to take data from. Invalid afterwards.
   * @return Reference to this Buffer.
   */
  Buffer& operator=(Buffer&& other) {  // NOLINT
    delete[] data_;
    num_elements_ = other.num_elements_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.num_elements_ = 0;
    return *this;
  }

  /**
   * @brief Returns size of buffer, in bytes.
   * @return
   */
  std::uint64_t SizeInBytes() const {
    return num_elements_ * sizeof(T);
  }

  /**
   * @brief Sets a value inside buffer.
   *
   * Nothing is done if an invalid index is provided.
   *
   * @param index Index at which to set value.
   * @param value Value to set.
   */
  void SetDataValue(const BufferIndex index, const T& value) {
    if (index >= 0 && index < num_elements_) {
      data_[index] = value;
    }
  }

  /**
   * @brief Accessor.
   * @return Number of elements in buffer.
   */
  const BufferIndex num_elements() const {
    return num_elements_;
  }

  /**
   * @brief Accessor.
   * @return Access to data stored in Buffer.
   */
  const T* data() const {
    return data_;
  }

 private:
  /// Number of elements stored.
  BufferIndex num_elements_;

  /// The data owned by this Buffer.
  T* data_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_MEMORY_BUFFER_H_
