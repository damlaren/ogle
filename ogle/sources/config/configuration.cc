/**
 * @file configuration.cc
 * @brief Implementation of configuration.h.
 */

#include "config/configuration.h"
#include "file_system/file_path.h"
#include "file_system/yaml_file.h"

namespace ogle {

bool Configuration::Load(const FilePath& file_path) {
  return yaml_file_.Load(file_path);
}

}  // namespace ogle
