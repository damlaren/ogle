/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Timer.
 */

#ifndef OGLE_INCLUDES_TIME_TIMER_H_
#define OGLE_INCLUDES_TIME_TIMER_H_

#include "std/ogle_std.inc"
#include <chrono>  // NOLINT

namespace ogle {

/**
 * @brief A generic timer giving elapsed time in real-world seconds.
 */
class Timer {
 public:
  /**
   * @brief Resets epoch.
   */
  void Reset();

  /**
   * @brief Measures time elapsed since epoch.
   * @return Time in seconds.
   */
  double Measure() const;

 private:
  /// Point which time is measured against.
  std::chrono::high_resolution_clock::time_point epoch_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_TIME_TIMER_H_
