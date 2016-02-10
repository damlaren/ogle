/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Buffer.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_BUFFER_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_BUFFER_H_

#include <algorithm>
#include <iterator>

namespace ogle {

/// Type for indexing into a Buffer.
using BufferIndex = std::uint32_t;

/**
 * @brief Memory buffer class that cleans up after itself.
 */
template<typename T>
class Buffer {
 public:
  // TODO(damlaren): Made for geometry, but not a geometric idea.

  /**
   * @brief Constructor. Creates a buffer of requested size.
   *
   * Doesn't initialize values in buffer.
   *
   * @param num_elements How many elements to reserve.
   */
  explicit Buffer(BufferIndex num_elements = 0) :
      num_elements_(num_elements) {
    data_ = new T[num_elements_];
  }

  /**
   * @brief Constructor. Creates a buffer from initializer list.
   * @param init_list Initial elements to copy.
   */
  Buffer(std::initializer_list<T> init_list) :
      num_elements_(init_list.size()) {
    data_ = new T[num_elements_];
    if (num_elements_ > 0) {
      std::copy(init_list.begin(), init_list.end(), data_);
    }
  }

  /**
   * @brief Constructor. Creates a buffer that wraps existing array.
   * @param data Array that is taken as Buffer storage.
   * @param num_elements How many elements are in array.
   */
  Buffer(T* data, BufferIndex num_elements) :
    num_elements_(num_elements),
    data_(data) {
  }

  /**
   * @brief Copy constructor.
   * @param other Buffer to copy contents from. Shallow.
   */
  Buffer(const Buffer& other) :
      num_elements_(other.num_elements_) {
    data_ = new T[num_elements_];
    if (num_elements_ > 0) {
      std::copy_n(other.data_, num_elements_, data_);
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
    delete[] data_;
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
      data_ = new T[num_elements_];
    }
    if (num_elements_ > 0) {
      std::copy_n(other.data_, num_elements_, data_);
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
   * @brief See return value.
   * @return Return size of buffer, in bytes.
   */
  std::uint64_t SizeInBytes() const {
    return num_elements_ * sizeof(T);
  }

  /// Number of elements stored.
  BufferIndex num_elements_;

  /// The data owned by this Buffer.
  T* data_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_BUFFER_H_
