/**
 * @file string_utils.h
 * @brief Defines StringUtils.
 */

#ifndef OGLE_INCLUDES_UTIL_STRING_UTILS_H_
#define OGLE_INCLUDES_UTIL_STRING_UTILS_H_

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

  /**
   * @brief Creates lowercase string.
   * @param input String to downcase.
   * @return New string.
   */
  static const stl_string Lower(const stl_string& input);

  /**
   * @brief Creates uppercase string.
   * @param input String to upcase.
   * @return New string.
   */
  static const stl_string Upper(const stl_string& input);
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_UTIL_STRING_UTILS_H_
