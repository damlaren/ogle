/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Functions for creating file paths.
 */

#ifndef OGLE_INCLUDES_FILE_SYSTEM_FILE_PATH_H_
#define OGLE_INCLUDES_FILE_SYSTEM_FILE_PATH_H_

#include "std/ogle_std.inc"

namespace ogle {

/**
 * @brief A class encapsulating a file or directory path.
 */
class FilePath {
 public:
  /// Separator between path elements.
  static constexpr char kPathSeparator = '/';

  /**
   * @brief Default constructor. Sets empty file path.
   */
  FilePath() = default;

  /**
   * @brief Constructor.
   * @param file_path String declaring path.
   */
  explicit FilePath(const stl_string& path);

  /**
   * @brief Joins two file paths with a path separator.
   * @param file_path_1 First part of path.
   * @param file_path_2 Second part of path.
   * @return Joined file paths.
   */
  friend const FilePath operator+(const FilePath& file_path_1,
                                  const FilePath& file_path_2);

  /**
   * @brief Output stream operator.
   * @param[in,out] os Output stream.
   * @param[in] file_path Object to print.
   * @return Reference to #os.
   */
  friend std::ostream& operator<<(std::ostream& os,  // NOLINT
                                  const FilePath& file_path);

  /**
   * @brief Accessor.
   * @return Reference to path string.
   */
  const stl_string& str() const;

  /**
   * @brief Gets filename extension.
   * @return Extension. Empty string if none found.
   */
  const stl_string Extension() const;

  /**
   * @brief Gets directory part of filename.
   *
   * Directories are not converted to absolute paths.
   *
   * @return Directory path. Empty string if no directory part.
   */
  const FilePath Dirname() const;

 private:
  /// File path as string.
  stl_string path_string_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_FILE_SYSTEM_FILE_PATH_H_
