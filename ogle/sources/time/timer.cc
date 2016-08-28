/**
 * @file timer.cc
 * @brief Implementation of timer.h.
 */

#include "time/timer.h"

namespace ogle {

void Timer::Reset() { epoch_ = std::chrono::high_resolution_clock::now(); }

double Timer::Measure() const {
  std::chrono::duration<double> seconds =
      std::chrono::high_resolution_clock::now() - epoch_;
  return seconds.count();
}

}  // namespace ogle
