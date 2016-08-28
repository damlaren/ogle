/**
 * @file default_allocator.h
 * @brief Defines default memory allocation strategies.
 *
 * This allocation strategy makes minimal changes, reusing the default STL
 * allocator and C++ new/delete operators.
 */

#ifndef OGLE_INCLUDES_STD_DEFAULT_ALLOCATOR_H_
#define OGLE_INCLUDES_STD_DEFAULT_ALLOCATOR_H_

#include <memory>

namespace ogle {

/**
 * @brief Basic allocator implementation.
 *
 * Reuses std::allocator.
 */
template<typename T>
using STLAllocator = std::allocator<T>;

}  // namespace ogle

#endif  // OGLE_INCLUDES_STD_DEFAULT_ALLOCATOR_H_
