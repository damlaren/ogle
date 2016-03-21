/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines StringUtils.
 */

#ifndef LIBRARIES_UTIL_INCLUDES_UTIL_STRING_UTILS_H_
#define LIBRARIES_UTIL_INCLUDES_UTIL_STRING_UTILS_H_

#include "std/ogle_std.inc"

namespace ogle {

/**
 * @brief Provides string manipulation utilities.
 */
class StringUtils {
 public:
  /**
   * @brief Replace tokens in string.
   * @param input String in which to replace tokens.
   * @param to_replace Character to replace.
   * @param replacement New character after replacement.
   * @return New string.
   */
  static const stl_string Replace(const stl_string& input,
                                  const char to_replace,
                                  const char replacement);
  /**
   * @brief Creates a string split by delimiters.
   * @param input String to split.
   * @param delim Delimiter for splitting string into tokens.
   * @return Split tokens.
   */
  static const stl_vector<stl_string> Split(const stl_string& input,
                                            const char delim);

  /**
   * @brief Creates a string with characters trimmed from the start and end.
   * @param input String to trim.
   * @param chars Characters to trim.
   * @return New string.
   */
  static const stl_string Trim(const stl_string& input,
                               const stl_string& chars);
};

}  // namespace ogle

#endif  // LIBRARIES_UTIL_INCLUDES_UTIL_STRING_UTILS_H_
