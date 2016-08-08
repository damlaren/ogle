/**
 * @file Implements string_utils.h.
 */

#include "util/string_utils.h"
#include <algorithm>
#include <sstream>

namespace ogle {

const stl_string StringUtils::Replace(const stl_string& input,
                                      const char to_replace,
                                      const char replacement) {
  stl_string new_string{input};
  std::replace(new_string.begin(), new_string.end(), to_replace, replacement);
  return new_string;
}

const stl_vector<stl_string> StringUtils::Split(const stl_string& input,
                                                const char delim) {
  std::stringstream input_stream(input);
  stl_string next_token;
  stl_vector<stl_string> tokens;

  while (std::getline(input_stream, next_token, delim)) {
    if (!next_token.empty()) {
      tokens.emplace_back(next_token);
    }
  }
  return tokens;
}

const stl_string StringUtils::Trim(const stl_string& input,
                                   const stl_string& chars) {
  // Trim left side.
  auto keep_index = input.find_first_not_of(chars);
  stl_string trimmed = (keep_index != stl_string::npos)?
      input.substr(keep_index) : "";

  // Trim right side.
  keep_index = trimmed.find_last_not_of(chars);
  trimmed = (keep_index != stl_string::npos)?
      trimmed.substr(0, keep_index + 1) : "";

  return trimmed;
}

const stl_string StringUtils::Lower(const stl_string& input) {
  stl_string result = input;
  std::transform(input.begin(), input.end(), result.begin(),
                 [](const char c) { return std::tolower(c); });
  return result;
}

const stl_string StringUtils::Upper(const stl_string& input) {
  stl_string result = input;
  std::transform(input.begin(), input.end(), result.begin(),
                 [](const char c) { return std::toupper(c); });
  return result;
}

}  // namespace ogle
