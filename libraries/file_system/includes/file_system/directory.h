/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Directory.
 */

#ifndef LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_DIRECTORY_H_
#define LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_DIRECTORY_H_

#include "std/ogle_std.inc"
#include <utility>
#include "file_system/file_path.h"

namespace ogle {

/**
 * @brief A single entry (file or subdirectory) found within a directory.
 */
class DirectoryEntry {
 public:
  /**
   * @brief List contents under a directory path.
   * @param directory_path Path to list contents of.
   * @return Directory entries found, and success/failure flag.
   */
  static std::pair<stl_vector<DirectoryEntry>, bool> ListContents(
      const FilePath& directory_path);

  /**
   * @brief Accessor.
   * @return Path to directory entry.
   */
  const FilePath& path() const;

  /**
   * @brief Accessor.
   * @return true if entry is a directory.
   */
  const bool is_directory() const;

 private:
  /**
   * @brief Constructor.
   * @param path Entry path.
   * @param is_directory true if this is a directory.
   */
  DirectoryEntry(const FilePath& path, const bool is_directory);

  /// Path to directory entry.
  FilePath path_;

  /// true if this entry is a directory.
  bool is_directory_;
};

}  // namespace ogle

#endif  // LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_DIRECTORY_H_
