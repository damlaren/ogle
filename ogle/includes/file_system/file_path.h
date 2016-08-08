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
