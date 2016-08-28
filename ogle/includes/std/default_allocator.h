/**
 * @file default_allocator.h
 * @brief Defines default memory allocation strategies.
 *
 * This allocation strategy makes minimal changes, reusing the default STL
 * allocator and C++ new/delete operators.
 */

#pragma once

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

