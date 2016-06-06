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
 *
 * KeyType is used to uniquely identify nodes. ValueType describes the data
 * stored in each node.
 */
template<typename KeyType, typename ValueType>
class DirectedGraph {
 public:
  /**
   * @brief A node in the graph.
   *
   * Identified by a unique key kept by the graph.
   */
  class Node {
   public:
    friend class DirectedGraph;

    /**
     * @brief Constructor.
     * @param value Value to store in node.
     */
    explicit Node(const ValueType& value)
      : value_(value) {
    }

    /**
     * @brief Accessor.
     * @return See #neighbors_.
     */
    const stl_vector<Node*>& neighbors() const {
      return neighbors_;
    }

    /**
     * @brief Accessor.
     * @return See #back_pointers_.
     */
    const stl_vector<Node*>& back_pointers() const {
      return back_pointers_;
    }

    /// Value to store in node.
    ValueType value_;

   private:
    /// Nodes this node has an edge to.
    stl_vector<Node*> neighbors_;

    /// Nodes with an edge back to this node.
    stl_vector<Node*> back_pointers_;
  };

  /**
   * @brief Function type to check if node matches search criteria.
   */
  using MatchFunction = bool(const Node* node);

  /**
   * @brief Add a node to graph without any edges.
   * @param key Unique key to identify new node.
   * @param value Value to store in node.
   * @return true if node was inserted, false if key is duplicate.
   */
  const bool AddNode(const KeyType& key, const ValueType& value) {
    return nodes_.emplace(key, Node(value)).second;
  }

  /**
   * @brief Add a directed edge to the graph.
   *
   * Both nodes must exist, and the edge must not always exist.
   *
   * @param src_key Identifies source node on edge.
   * @param dest_key Identifies destination node on edge.
   * @return true if edge was added successfully.
   */
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

  /**
   * @brief Get value from node.
   * @param key Identifies node to get value from.
   * @return Pair containing (1) Retrieved value, and (2) flag indicating
   *         whether node was found.
   */
  const std::pair<const ValueType&, bool> GetValue(const KeyType& key) const {
    const auto it = nodes_.find(key);
    if (it != nodes_.end()) {
      return {it->second.value_, true};
    }
    return {{}, false};
  }

  /**
   * @brief Get neighbors that a node has edges to.
   * @param key Identifies node to query.
   * @return Pair containing (1) Neighboring nodes, and (2) flag indicating
   *         whether node with this key was found.
   */
  const std::pair<stl_vector<Node*>, bool> GetNeighbors(
      const KeyType& key) const {
    const auto node_it = nodes_.find(key);
    if (node_it != nodes_.end()) {
      return {node_it->neighbors_, true};
    }
    return {{}, false};
  }

  /**
   * @brief Remove a node and all connecting edges from the graph.
   * @param key Identifies node to remove.
   * @return Flag indicating whether node was removed.
   */
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

  /**
   * @brief Retrieves nodes matching a condition.
   * @param match_function A #MatchFunction to test conditions on a Node.
   * @return Keys and values for all nodes matching the condition.
   */
  stl_vector<std::pair<const KeyType&, ValueType*>> GetMatches(
      MatchFunction match_function) {
    stl_vector<std::pair<const KeyType&, ValueType*>> results;
    for (auto it = nodes_.begin(); it != nodes_.end(); it++) {
      if (match_function(&it->second)) {
        results.emplace_back(it->first, &it->second.value_);
      }
    }
    return results;
  }

 private:
  /// All nodes in graph, keyed by unique ID.
  stl_unordered_map<KeyType, Node> nodes_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ALGORITHMS_DIRECTED_GRAPH_H_
