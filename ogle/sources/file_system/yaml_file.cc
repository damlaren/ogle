/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of yaml_file.h.
 */

#include "file_system/yaml_file.h"
#include <iostream>
#include <sstream>
#include "yaml-cpp/yaml.h"
#include "file_system/file_path.h"
#include "std/new_wrappers.h"

namespace ogle {

/**
 * @brief Data loaded from YAML file.
 */
struct YAMLFile::Data {
  YAML::Node root_node_;  ///< Root node loaded from file.
};

YAMLFile::YAMLFile() {
  data_ = AllocateObject<YAMLFile::Data>();
}

YAMLFile::~YAMLFile() {
  delete data_;
}

YAMLFile::YAMLFile(const YAMLFile& rhs) {
  *this = rhs;
}

YAMLFile& YAMLFile::operator=(const YAMLFile& rhs) {
  data_ = AllocateObject<YAMLFile::Data>();
  data_->root_node_ = YAML::Node(rhs.data_->root_node_);
  return *this;
}

std::ostream& operator<<(std::ostream& os, const YAMLFile& yaml_file) {
  os << yaml_file.data_->root_node_;
  return os;
}

bool YAMLFile::Load(const FilePath& file_path) {
  data_->root_node_ = YAML::LoadFile(file_path.str());
  if (!data_->root_node_) {
    LOG(ERROR) << "Failed to load YAML from: " << file_path.str();
    return false;
  }
  return true;
}

template <typename T>
const T YAMLFile::Get(const stl_vector<stl_string>& keys) const {
  if (!data_) {
    LOG(ERROR) << "No data loaded for YAML file.";
    return T{};
  }
  if (data_->root_node_ && !keys.empty()) {
    // yaml-cpp resets data held by a node on assignment, which necessitates
    // this weird workaround.
    std::vector<YAML::Node> node_hierarchy;

    node_hierarchy.emplace_back(data_->root_node_);
    for (const auto& key : keys) {
      const auto& last_node = node_hierarchy.back();
      if (last_node) {
        node_hierarchy.emplace_back(last_node[key]);
      }
    }
    const auto& last_node = node_hierarchy.back();
    if (last_node) {
      return last_node.as<T>();
    }
  }

  std::ostringstream oss;
  std::copy(keys.begin(), keys.end(),
            std::ostream_iterator<stl_string>(oss, ","));
  LOG(ERROR) << "Keys not found in YAML file: " << oss.str();
  return T{};
}

// Declarations of used Getters.
template const stl_string YAMLFile::Get<stl_string>(
    const stl_vector<stl_string>& keys) const;
template const int YAMLFile::Get<int>(
    const stl_vector<stl_string>& keys) const;
template const stl_vector<stl_string> YAMLFile::Get<stl_vector<stl_string>>(
    const stl_vector<stl_string>& keys) const;

}  // namespace ogle
