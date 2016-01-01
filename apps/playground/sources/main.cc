/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file A sandbox for trying out new features.
 */

#include <iostream>
#include "ogle/ogle.h"

using std::cout;
using std::endl;
using Vector3f = ogle::Vector3f;

void TestVector() {
  ogle::Vector<double, 1> v1;
  ogle::Vector<double, 2> v2;
  ogle::Vector<double, 3> v3;
  ogle::Vector<double, 4> v4;

  v4.w();

  ogle::Vector<double, 2> v5{0.0, 1.0};
  ogle::Vector<double, 2> v6(0.0, 1.0);
  const double test[2] = {0, 1};
  ogle::Vector<double, 2> v7(test);
  double test2[2] = {0, 1};
  ogle::Vector<double, 2> v8(test);

  Vector3f p1{0, 1, 0};
  Vector3f p2{-1, 0, 0};
  Vector3f r1 = p1 + p2;
  cout << r1 << endl;  // -1,1,0
  p1 += p2;
  cout << p1 << endl;  // -1,1,0
  cout << -r1 << endl;  // 1,-1,0
  cout << p1 - p2 << endl;  // 0,1,0
  r1 -= p1;
  cout << r1 << endl;  // 0,0,0

  Vector3f d1(1, 2, 3);
  Vector3f d2(1, 0, -1);
  cout << d1 * d2 << endl;  // -2
  cout << d1.Dot(d2) << endl;  // -2
  cout << d1 * 2 << endl;  // 2,4,6
  cout << d1 / 2.0 << endl;  // 0.5,1,1.5
}

void TestMatrix() {
  ogle::Matrix<double, 3, 3> m33;
  m33.Clear();
}

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main() {
  TestVector();
  TestMatrix();

  return 0;
}
