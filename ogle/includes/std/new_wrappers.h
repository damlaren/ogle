/**
 * @file new_wrappers.h
 * @brief Defines wrappers for allocation functions.
 */

#ifndef OGLE_INCLUDES_STD_NEW_WRAPPERS_H_
#define OGLE_INCLUDES_STD_NEW_WRAPPERS_H_

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
  T* new_object = new T(std::forward<Args>(args)...);
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
  auto new_object = std::make_unique<T>(std::forward<Args>(args)...);
  CHECK(new_object != nullptr) << "Unique object allocation failed.";
  return std::move(new_object);
}

#endif  // OGLE_INCLUDES_STD_NEW_WRAPPERS_H_

