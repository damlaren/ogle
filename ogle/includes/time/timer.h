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
