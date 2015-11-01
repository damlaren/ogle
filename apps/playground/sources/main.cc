/**
 * @file A sandbox for trying out new features.
 */

#include <iostream>

#include "ogle/math/includes/core/vector.h"

/**
 * @brief main Main entry point.
 * @return 0 on success, something else on failure.
 */

int main() {
  ogle::math::Vector<double, 1> v1;
  ogle::math::Vector<double, 2> v2;
  ogle::math::Vector<double, 3> v3;
  ogle::math::Vector<double, 4> v4;

  v4.w();

  ogle::math::Vector<double, 2> v5{0.0, 1.0};
  ogle::math::Vector<double, 2> v6(0.0, 1.0);
  const double test[2] = {0, 1};
  ogle::math::Vector<double, 2> v7(test);
  double test2[2] = {0, 1};
  ogle::math::Vector<double, 2> v8(test);

  return 0;
}
