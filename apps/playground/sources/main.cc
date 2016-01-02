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

/**
 * @brief Validate Vector operations.
 */
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

  Vector3f p1{0.0f, 1.0f, 0.0f};
  Vector3f p2{-1.0f, 0.0f, 0.0f};
  Vector3f r1 = p1 + p2;
  cout << r1 << endl;  // -1,1,0
  p1 += p2;
  cout << p1 << endl;  // -1,1,0
  cout << -r1 << endl;  // 1,-1,0
  cout << p1 - p2 << endl;  // 0,1,0
  r1 -= p1;
  cout << r1 << endl;  // 0,0,0

  Vector3f d1(1.0f, 2.0f, 3.0f);
  Vector3f d2(1.0f, 0.0f, -1.0f);
  cout << d1 * d2 << endl;  // -2
  cout << d1.Dot(d2) << endl;  // -2
  cout << d1 * 2 << endl;  // 2,4,6
  cout << d1 / 2.0 << endl;  // 0.5,1,1.5
  cout << d1.Cross(d2) << endl;  // -2,4,-2
  cout << d1.Expanded(1.0f) << endl;  // 1,2,3,1
  cout << d1.Shrunk() << endl;  // 1,2
}

/**
 * @brief Validate Matrix operations.
 */
void TestMatrix() {
  ogle::Matrix<float, 3, 3> m33, n33;
  m33.Clear();
  m33.Set(1.0f);
  auto eye33 = ogle::Matrix<float, 3, 3>::Identity();
  cout << m33 << endl;  // 3x3, all 1.
  cout << m33 + eye33 << endl;  // 3x3, 2 on diag, 1 elsewhere.
  cout << m33 - eye33 << endl;  // 3x3, 0 on diag, 1 elsewhere.
  cout << m33 * 2 << endl;  // 3x3, all 2.
  cout << m33 / 2 << endl;  // 3x3, all 0.5.

  ogle::Matrix<float, 1, 2> m12;
  ogle::Matrix<float, 2, 1> m21;
  m12(0, 0) = 1.0f;
  m12(0, 1) = 2.0f;
  m21(0, 0) = -1.0f;
  m21(1, 0) = 2.0f;
  cout << m12 << endl;  // [1 2] (row).
  cout << m21 << endl;  // [-1; 2] (column).
  cout << m21.Transpose() << endl;  // [-1 2] (row).
  cout << m12 * m21 << endl;  // [3]
  cout << m21 * m12 << endl;  // [-1 -2; 2 4]

  ogle::Matrix<float, 1, 1> m11, n11;
  ogle::Matrix<float, 2, 2> m22, n22;
  m11.Set(2);
  m22(0, 0) = 4;
  m22(0, 1) = 3;
  m22(1, 0) = 3;
  m22(1, 1) = 2;
  cout << m11.Determinant() << endl;  // 2
  cout << m22.Determinant() << endl;  // -1
  m33.Determinant();
  ogle::Matrix<float, 4, 4> m44, n44;
  m44.Determinant();

  m11.Inverse(&n11);  // [0.5]
  m22.Inverse(&n22);  // [-2 3; 3 -4]
  m33.Inverse(&n33);
  m44.Inverse(&n44);
  cout << n11 << endl
       << n22 << endl;
}

/**
 * @brief Try out Matrix-Vector interaction.
 */
void TestMatrixVector() {
  Vector3f v3;
  ogle::Matrix<float, 1, 3> m13;
  ogle::Matrix<float, 3, 1> m31 = ogle::Matrix<float, 3, 1>::AsMatrix(v3);
  Vector3f vtest = m31.AsVector();
}

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main() {
  TestMatrixVector();

  return 0;
}
