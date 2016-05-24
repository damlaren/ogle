/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines wrappers for allocation functions.
 */

#ifndef LIBRARIES_STD_INCLUDES_STD_NEW_WRAPPERS_H_
#define LIBRARIES_STD_INCLUDES_STD_NEW_WRAPPERS_H_

#include "easylogging++.h"  // NOLINT

/**
 * @brief Allocates an object using new operator.
 *
 * A fatal error occurs if allocation fails.
 *
 * @param args Arguments to pass to object constructor.
 * @return Pointer to newly constructed object.
 */
template<class T, class... Args>
T* AllocateObject(Args&&... args) {
  T* new_object = new T(args...);
  CHECK(new_object != nullptr) << "Object allocation failed.";
  return new_object;
}

/**
 * @brief Allocates a buffer using new operator.
 *
 * A fatal error occurs if allocation fails.
 *
 * @param count Number of elements to allocate in buffer.
 * @return Pointer to new buffer.
 */
template<class T>
T* AllocateBuffer(const std::size_t count) {
  T* new_buffer = new T[count];
  CHECK(new_buffer != nullptr) << "Buffer allocation failed.";
  return new_buffer;
}

/**
 * @brief Creates a unique pointer to a new object.
 *
 * A fatal error occurs if allocation fails.
 *
 * @param args Arguments to pass to object constructor.
 * @return Unique pointer to new object.
 */
template<class T, class... Args>
std::unique_ptr<T> AllocateUniqueObject(Args&&... args) {
  auto new_object = std::make_unique<T>(args...);
  CHECK(new_object != nullptr) << "Unique object allocation failed.";
  return std::move(new_object);
}

#endif  // LIBRARIES_STD_INCLUDES_STD_NEW_WRAPPERS_H_

