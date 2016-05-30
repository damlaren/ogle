/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
