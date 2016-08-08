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
const std::pair<T, bool> YAMLFile::Get(
    const stl_vector<stl_string>& keys) const {
  if (!data_) {
    LOG(ERROR) << "No data loaded for YAML file.";
    return {T{}, false};
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
      return {last_node.as<T>(), true};
    }
  }

  std::ostringstream oss;
  std::copy(keys.begin(), keys.end(),
            std::ostream_iterator<stl_string>(oss, ","));
  return {T{}, false};
}

// Declarations of used Getters.
template const std::pair<stl_string, bool>
YAMLFile::Get<stl_string>(const stl_vector<stl_string>& keys) const;

template const std::pair<int, bool>
YAMLFile::Get<int>(const stl_vector<stl_string>& keys) const;

template const std::pair<float, bool>
YAMLFile::Get<float>(const stl_vector<stl_string>& keys) const;

template const std::pair<double, bool>
YAMLFile::Get<double>(const stl_vector<stl_string>& keys) const;

template const std::pair<stl_vector<stl_string>, bool>
YAMLFile::Get<stl_vector<stl_string>>(const stl_vector<stl_string>& keys) const;

}  // namespace ogle
