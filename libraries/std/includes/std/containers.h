/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines STL containers with custom allocators.
 */

#ifndef LIBRARIES_STD_INCLUDES_STD_CONTAINERS_H_
#define LIBRARIES_STD_INCLUDES_STD_CONTAINERS_H_

#include "std/custom_allocator.h"

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ogle {

template <typename K, typename V, typename C = std::less<K>>
using stl_map = std::map<K, V, C, STLAllocator<std::pair<const K, V>>>;

using stl_string =
    std::basic_string<char, std::char_traits<char>, STLAllocator<char>>;

template <typename K, typename V, typename H = std::hash<K>,
          typename E = std::equal_to<K>>
using stl_unordered_map =
    std::unordered_map<K, V, H, E, STLAllocator<std::pair<const K, V>>>;

template <typename T>
using stl_vector = std::vector<T, STLAllocator<T>>;

}  // namespace ogle

#endif  // LIBRARIES_STD_INCLUDES_STD_CONTAINERS_H_
