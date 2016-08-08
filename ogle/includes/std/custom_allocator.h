/**
 * @file Defines which custom memory allocators to use.
 *
 * Redefines both STL allocators and global C++ new/delete operators.
 * This is done simply by including a header file for the desired allocation
 * strategy.
 *
 * Some invaluables notes are collected here:
 *
 * - Redefining C++ new and delete
 *   http://en.cppreference.com/w/cpp/memory/new/operator_new
 * - STL Allocators in C++ and std::allocator
 *   - http://en.cppreference.com/w/cpp/concept/Allocator
 *   - http://en.cppreference.com/w/cpp/memory/allocator
 *   - An example: http://www.josuttis.com/cppcode/myalloc.hpp.html
 * - Motivation for allocators in game development and EASTL
 *   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2271.html
 */

#ifndef OGLE_INCLUDES_STD_CUSTOM_ALLOCATOR_H_
#define OGLE_INCLUDES_STD_CUSTOM_ALLOCATOR_H_

#include "std/default_allocator.h"

#endif  // OGLE_INCLUDES_STD_CUSTOM_ALLOCATOR_H_
