/**
 * @file text_file.h
 * @brief Defines TextFile.
 */

#pragma once

#include "std/ogle_std.inc"
#include "file_system/file_path.h"

namespace ogle {

/**
 * @brief Convenience functions for I/O on text files
 */
class TextFile {
 public:
  /**
   * @brief Read all contents of a file.
   * @param file_path Path to file to read.
   * @param[out] text Contents read from file.
   * @return Whether the operation was completed successfully.
   */
  static const bool ReadTextFile(const FilePath& file_path, stl_string* text);
};

}  // namespace ogle

