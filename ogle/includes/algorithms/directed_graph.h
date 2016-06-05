/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines DirectedGraph.
 */

#ifndef OGLE_INCLUDES_ALGORITHMS_DIRECTED_GRAPH_H_
#define OGLE_INCLUDES_ALGORITHMS_DIRECTED_GRAPH_H_

#include "std/ogle_std.inc"
#include <functional>
#include <utility>
#include <vector>
#include "easylogging++.h"  // NOLINT

namespace ogle {

/**
 * @brief A directed graph.
 */
template<typename KeyType, typename ValueType>
class DirectedGraph {
 public:
  class Node {
   public:
    friend class Graph;

    Node(KeyType&& key, ValueType&& value)  // NOLINT
      : key_(std::forward<KeyType>(key)),
        value_(std::forward<ValueType>(value)) {
    }

    const KeyType& key() const {
      return key_;
    }

    const stl_vector<Node*>& neighbors() const {
      return neighbors_;
    }

    const stl_vector<Node*>& back_pointers() const {
      return back_pointers_;
    }

    ValueType value_;

   private:
    KeyType key_;
    stl_vector<Node*> neighbors_;
    stl_vector<Node*> back_pointers_;
  };

  using MatchFunction = bool(const Node* node);

  const bool AddNode(KeyType&& key, ValueType&& value) {  // NOLINT
    return nodes_.emplace(std::forward<KeyType>(key),
                          std::forward<ValueType>(value)).second;
  }

  const bool AddEdge(KeyType&& src_key, KeyType&& dest_key) {  // NOLINT
    auto src_it = nodes_.find(src_key);
    if (src_it == nodes_.end()) {
      return false;
    }
    auto dest_it = nodes_.find(dest_key);
    if (dest_it == nodes_.end()) {
      return false;
    }

    Node* src_node = *src_it;
    Node* dest_node = *dest_it;
    CHECK(src_node != nullptr && dest_node != nullptr)
        << "Both nodes must exist if keys are found to add an edge.";
    auto back_it = std::find(dest_node->back_pointers_.begin(),
                             dest_node->back_pointers_.end(), src_node);
    if (std::find(src_node->neighbors_.begin(), src_node->neighbors_.end(),
                  dest_node) != src_node->neighbors_.end()) {
      CHECK(back_it != dest_node->back_pointers_.end())
          << "Expected to find back pointer.";
      return false;
    }
    CHECK(back_it == dest_node->back_pointers_.end())
        << "Expected not to find back pointer.";
    src_node->neighbors_.emplace_back(dest_node);
    dest_node->back_pointers_.emplace_back(src_node);
    return true;
  }

  const std::pair<const ValueType&, bool> GetValue(const KeyType& key) const {
    const auto it = nodes_.find(key);
    if (it != nodes_.end()) {
      return {it->second, true};
    }
    return {nullptr, false};
  }

  const std::pair<std::vector<Node*>, bool> GetNeighbors(
      const KeyType& key) const {
    const auto node_it = nodes_.find(key);
    if (node_it != nodes_.end()) {
      return {node_it->neighbors_, true};
    }
    return {{}, false};
  }

  const bool Remove(const KeyType& key) {
    auto node_it = nodes_.find(key);
    if (node_it != nodes_.end()) {
      Node* node = *node_it;
      for (Node* dest_node : node->neighbors_) {
        dest_node->back_pointers_.erase(std::find(
            dest_node->back_pointers_.begin(), dest_node->back_pointers_.end(),
            node));
      }
      for (Node* src_node : node->back_pointers_) {
        src_node->neighbors_.erase(std::find(
            src_node->neighbors_.begin(), src_node->neighbors_.end(), node));
      }
      nodes_.erase(node_it);
      return true;
    }
    return false;
  }

  std::vector<Node*> GetMatchingNodes(MatchFunction match_function) const {
    std::vector<Node*> results;
    std::copy_if(nodes_.begin(), nodes_.end(), std::back_inserter(results),
                 match_function);
    return results;
  }

 private:
  stl_unordered_set<Node, std::hash<KeyType>, std::equal_to<KeyType>> nodes_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ALGORITHMS_DIRECTED_GRAPH_H_
