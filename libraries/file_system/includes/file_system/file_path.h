/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Functions for creating file paths.
 */

#ifndef LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_FILE_PATH_H_
#define LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_FILE_PATH_H_

#include "std/ogle_std.inc"

namespace ogle {

namespace file_system {

/**
 * @brief Joins two file paths with a path separator.
 * @param file_path_1 First part of path.
 * @param file_path_2 Second part of path.
 * @return Joined file paths.
 */
const stl_string JoinPaths(const stl_string& file_path_1,
                           const stl_string& file_path_2);

}  // namespace file_system

}  // namespace ogle

#endif  // LIBRARIES_FILE_SYSTEM_INCLUDES_FILE_SYSTEM_FILE_PATH_H_
