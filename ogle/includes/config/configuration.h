/**
 * @file configuration.h
 * @brief Defines Configuration.
 */

#ifndef OGLE_INCLUDES_CONFIG_CONFIGURATION_H_
#define OGLE_INCLUDES_CONFIG_CONFIGURATION_H_

#include "std/ogle_std.inc"
#include <utility>
#include "easylogging++.h"  // NOLINT
#include "file_system/yaml_file.h"

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
   * @return Pair with: (1) Retrieved value, or default-constructed object if
   *         nothing; and (2) flag indicating whether value was found.
   */
  template <typename T>
  const std::pair<T, bool> Get(const stl_string& module_name,
                               const stl_string& attribute_name) const {
    return yaml_file_.Get<T>({module_name, attribute_name});
  }

 private:
  /// Parsed YAML file with configuration data.
  YAMLFile yaml_file_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_CONFIG_CONFIGURATION_H_
