/**
 * @file Implementation of file_path.h.
 */

#include "file_system/file_path.h"

namespace ogle {

FilePath::FilePath(const stl_string &path)
  : path_string_(path) {
  size_t index = 0;
  while ((index = path_string_.find('\\', index)) != stl_string::npos) {
    path_string_[index] = kPathSeparator;
  }
}

const FilePath operator+(const FilePath& file_path_1,
                         const FilePath& file_path_2) {
  if (file_path_1.path_string_.empty()) {
    return file_path_2;
  } else if (file_path_2.path_string_.empty()) {
    return file_path_1;
  } else {
    return FilePath(file_path_1.path_string_ + "/" +
                    file_path_2.path_string_);
  }
}

std::ostream& operator<<(std::ostream& os, const FilePath& file_path) {
  os << file_path.str();
  return os;
}

const stl_string& FilePath::str() const {
  return path_string_;
}

const stl_string FilePath::Extension() const {
  const auto typeSeparatorIndex = path_string_.find_last_of(".");
  if (typeSeparatorIndex != stl_string::npos &&
      typeSeparatorIndex != path_string_.size() - 1) {
    return path_string_.substr(typeSeparatorIndex + 1);
  }
  return "";
}

const FilePath FilePath::Dirname() const {
  const auto lastSeparatorIndex = path_string_.find_last_of(kPathSeparator);
  if (lastSeparatorIndex != stl_string::npos) {
    return FilePath(path_string_.substr(0, lastSeparatorIndex));
  }
  return FilePath("");
}

}  // namespace ogle
