/**
 * @file Implementation of text_file.h.
 */

#include "file_system/text_file.h"
#include <fstream>
#include <sstream>
#include "easylogging++.h"  // NOLINT
#include "file_system/file_path.h"

namespace ogle {

const bool TextFile::ReadTextFile(const FilePath& file_path,
                                  stl_string* text) {
  std::ifstream in_file(file_path.str());
  if (!in_file.is_open()) {
    LOG(ERROR) << "Failed to open file: " << file_path.str();
    return false;
  }
  *text = stl_string(std::istreambuf_iterator<char>(in_file),
                     std::istreambuf_iterator<char>());
  return true;
}

}  // namespace ogle
