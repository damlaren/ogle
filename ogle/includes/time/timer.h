/**
 * @file timer.h
 * @brief Defines Timer.
 */

#pragma once

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

