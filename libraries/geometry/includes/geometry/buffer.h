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

/**
 * @brief Memory buffer class that cleans up after itself.
 *
 * TODO(damlaren): Made for geometry, but fits in a memory module.
 */
template<typename T>
class Buffer {
 public:
  /// Type for indexing into a Buffer.
  using BufferIndex = std::size_t;

  /**
   * @brief Creates a buffer of requested size.
   * @param num_elements How many elements to reserve.
   */
  Buffer(BufferIndex num_elements = 0) :
      num_elements_(num_elements) {
    data_ = new T[num_elements_];
  }

  /**
   * @brief Copy constructor.
   * @param other Buffer to copy contents from. Shallow.
   */
  Buffer(const Buffer& other) :
      num_elements_(other.num_elements_) {
    std::copy_n(other.data_, num_elements_, data_);
  }

  /**
   * @brief Move constructor.
   * @param other Buffer to take data from. Invalid afterwards.
   */
  Buffer(Buffer&& other) :
      num_elements_(other.num_elements_) {
    data_ = other.data_;
    other.data_ = nullptr;
  }

  /// @brief Deletes buffer.
  ~Buffer() {
    delete[] data_;
  }

  /**
   * @brief Copy assignment operator.
   * @param other Buffer to copy contents from. Shallow.
   * @return Reference to this Buffer.
   */
  Buffer& operator=(const Buffer& other) {
    num_elements_ = other.num_elements_;
    std::copy_n(other.data_, num_elements_, data_);
    return *this;
  }

  /**
   * @brief Move assignment operator.
   * @param other Buffer to take data from. Invalid afterwards.
   * @return Reference to this Buffer.
   */
  Buffer& operator=(Buffer&& other) {
    num_elements_ = other.num_elements_;
    data_ = other.data_;
    return *this;
  }

  /// Number of elements stored.
  BufferIndex num_elements_;

  /// The data owned by this Buffer.
  T* data_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_BUFFER_H_

