/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Configuration.
 */

#ifndef LIBRARIES_CONFIG_INCLUDES_CONFIG_CONFIGURATION_H_
#define LIBRARIES_CONFIG_INCLUDES_CONFIG_CONFIGURATION_H_

#include "std/ogle_std.inc"
#include "easylogging++.h"  // NOLINT
#include "yaml-cpp/yaml.h"

namespace ogle {

class FilePath;

/**
 * @brief Configuration for all ogle modules.
 *
 * Used by Engine to instantiate objects.
 *
 * There is one YAML configuration file for ogle. It is organized by the module
 * name and then key-value attribute pairs.
 */
class Configuration {
 public:
  /**
   * @brief Loads configuration from file.
   * @param file_path Name of file from which to load.
   * @return success/failure.
   */
  bool Load(const FilePath& file_path);

  /**
   * @brief Gets value of attribute configuration for a module.
   *
   * @param module_name Name of subsystem for which to look up attribute.
   * @param attribute_name Name of attribute to look up.
   * @return Retrieved value, or default-constructed object if nothing.
   */
  template <typename T>
  const T Get(const stl_string& module_name,
              const stl_string& attribute_name) const {
    if (root_node_) {
      const auto& module_node = root_node_[module_name];
      if (module_node) {
        const auto& attribute_node = module_node[attribute_name];
        if (attribute_node) {
          return attribute_node.as<T>();
        }
      }
    }
    LOG(ERROR) << "Configuration not found: " << module_name << "/"
               << attribute_name;
    return T{};
  }

 private:
  /// Root of loaded YAML file.
  YAML::Node root_node_;
};

}  // namespace ogle

#endif  // LIBRARIES_CONFIG_INCLUDES_CONFIG_CONFIGURATION_H_
