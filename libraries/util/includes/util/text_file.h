/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines TextFile.
 */

#ifndef LIBRARIES_UTIL_INCLUDES_UTIL_TEXT_FILE_H_
#define LIBRARIES_UTIL_INCLUDES_UTIL_TEXT_FILE_H_

#include <fstream>
#include <string>
#include <vector>

namespace ogle {

/**
 * @brief Convenience functions for I/O on text files.
 */
class TextFile {
 public:
  /**
   * @brief Read all contents of a file.
   * @param file_path Path to file to read.
   * @param[out] text Contents read from file.
   * @return Whether the operation was completed successfully.
   */
  static bool ReadFile(const std::string& file_path,
                       std::string* text);

  /**
   * @brief Split text into separate lines.
   * @param text Text to split.
   * @param[out] lines Vector containing each line of text.
   */
  static void SplitLines(const std::string& text,
                         std::vector<std::string>* lines);
};

}  // namespace ogle

#endif  // LIBRARIES_UTIL_INCLUDES_UTIL_TEXT_FILE_H_
