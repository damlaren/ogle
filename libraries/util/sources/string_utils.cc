/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements string_utils.h.
 */

#include "util/string_utils.h"
#include <algorithm>
#include <sstream>

namespace ogle {

const std::string StringUtils::Replace(const std::string& input,
                                       const char to_replace,
                                       const char replacement) {
  std::string new_string{input};
  std::replace(new_string.begin(), new_string.end(), to_replace, replacement);
  return new_string;
}

const std::vector<std::string> StringUtils::Split(const std::string& input,
                                                  const char delim) {
  std::stringstream input_stream(input);
  std::string next_token;
  std::vector<std::string> tokens;

  while (std::getline(input_stream, next_token, delim)) {
    if (!next_token.empty()) {
      tokens.emplace_back(next_token);
    }
  }
  return tokens;
}

const std::string StringUtils::Trim(const std::string& input,
                                    const std::string& chars) {
  // Trim left side.
  auto keep_index = input.find_first_not_of(chars);
  std::string trimmed = (keep_index != std::string::npos)?
      input.substr(keep_index) : "";

  // Trim right side.
  keep_index = trimmed.find_last_not_of(chars);
  trimmed = (keep_index != std::string::npos)?
      trimmed.substr(0, keep_index + 1) : "";

  return trimmed;
}

}  // namespace ogle
