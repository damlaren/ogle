/**
 * @file Defines STL containers with custom allocators.
 */

#ifndef OGLE_INCLUDES_STD_CONTAINERS_H_
#define OGLE_INCLUDES_STD_CONTAINERS_H_

#include "std/custom_allocator.h"

#include <functional>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace ogle {

template <typename T>
using stl_list = std::list<T, STLAllocator<T>>;

template <typename K, typename V, typename C = std::less<K>>
using stl_map = std::map<K, V, C, STLAllocator<std::pair<const K, V>>>;

using stl_string =
    std::basic_string<char, std::char_traits<char>, STLAllocator<char>>;

template <typename K, typename V, typename H = std::hash<K>,
          typename E = std::equal_to<K>>
using stl_unordered_map =
    std::unordered_map<K, V, H, E, STLAllocator<std::pair<const K, V>>>;

template <typename K, typename V, typename H = std::hash<K>,
          typename E = std::equal_to<K>>
using stl_unordered_multimap =
    std::unordered_multimap<K, V, H, E, STLAllocator<std::pair<const K, V>>>;

template <typename K, typename H = std::hash<K>, typename E = std::equal_to<K>>
using stl_unordered_set = std::unordered_set<K, H, E, STLAllocator<K>>;

template <typename T>
using stl_vector = std::vector<T, STLAllocator<T>>;

}  // namespace ogle

#endif  // OGLE_INCLUDES_STD_CONTAINERS_H_
