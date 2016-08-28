/**
 * @file directory.h
 * @brief Defines Directory.
 */

#pragma once

#include "std/ogle_std.inc"
#include <utility>
#include "file_system/file_path.h"

namespace ogle {

/**
 * @brief A single entry (file or subdirectory) found within a directory.
 */
class DirectoryEntry {
 public:
  /// Name of shortcut to current directory.
  static const stl_string kSameDirectoryName;

  /// Name of shortcut to parent directory.
  static const stl_string kParentDirectoryName;

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

  /**
   * @brief Tells if this is a link to same directory (e.g. ".")
   * @return As above.
   */
  const bool IsSameDirectoryLink() const;

  /**
   * @brief Tells if this is a link to parent directory (e.g. "..")
   * @return As above.
   */
  const bool IsParentDirectoryLink() const;

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

