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
    friend class DirectedGraph;

    explicit Node(const ValueType& value)
      : value_(value) {
    }

    const stl_vector<Node*>& neighbors() const {
      return neighbors_;
    }

    const stl_vector<Node*>& back_pointers() const {
      return back_pointers_;
    }

    ValueType value_;

   private:
    stl_vector<Node*> neighbors_;
    stl_vector<Node*> back_pointers_;
  };

  using MatchFunction = bool(const Node* node);

  const bool AddNode(const KeyType& key, const ValueType& value) {
    return nodes_.emplace(key, Node(value)).second;
  }

  const bool AddEdge(const KeyType& src_key, const KeyType& dest_key) {
    auto src_it = nodes_.find(src_key);
    if (src_it == nodes_.end()) {
      return false;
    }
    auto dest_it = nodes_.find(dest_key);
    if (dest_it == nodes_.end()) {
      return false;
    }

    Node* src_node = &src_it->second;
    Node* dest_node = &dest_it->second;
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
      return {it->second.value_, true};
    }
    return {{}, false};
  }

  const std::pair<stl_vector<Node*>, bool> GetNeighbors(
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
      Node* node = &node_it->second;
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

  /**
   * @brief Simple query.
   * @return true if graph has no nodes.
   */
  const bool Empty() const {
    return nodes_.empty();
  }

  /**
   * @brief Simple query.
   * @return Number of nodes in this graph.
   */
  const std::size_t Size() const {
    return nodes_.size();
  }

  stl_vector<std::pair<const KeyType&, ValueType*>> GetMatches(
      MatchFunction match_function) {
    stl_vector<std::pair<const KeyType&, ValueType*>> results;
    for (auto it = nodes_.begin(); it != nodes_.end(); it++) {
      results.emplace_back(it->first, &it->second.value_);
    }
    return results;
  }

 private:
  stl_unordered_map<KeyType, Node> nodes_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ALGORITHMS_DIRECTED_GRAPH_H_
