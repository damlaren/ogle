/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of angle.h.
 */

#include "math/angle.h"

namespace ogle {

Angle::Angle(const float radians)
  : theta_{radians} {
}

const Angle Angle::FromDegrees(const float degrees) {
  return Angle(degrees * kPi / 180.f);
}

const float Angle::radians() const noexcept {
  return theta_;
}

const float Angle::degrees() const noexcept {
  return theta_ * 180.f / kPi;
}

std::ostream& operator<<(std::ostream& os, const Angle rhs) {
  os << rhs.degrees() << "d";
  return os;
}

const Angle operator+(const Angle lhs, const Angle rhs) noexcept {
  return Angle(lhs) += rhs;
}

Angle& Angle::operator+=(const Angle rhs) noexcept {
  theta_ += rhs.theta_;
  return *this;
}

const Angle operator-(const Angle lhs, const Angle rhs) noexcept {
  return Angle(lhs) -= rhs;
}

Angle& Angle::operator-=(const Angle rhs) noexcept {
  theta_ -= rhs.theta_;
  return *this;
}

const Angle operator*(const Angle lhs, const Angle rhs) noexcept {
  return Angle(lhs) *= rhs;
}

Angle& Angle::operator*=(const Angle rhs) noexcept {
  theta_ *= rhs.theta_;
  return *this;
}

const Angle operator/(const Angle lhs, const Angle rhs) {
  return Angle(lhs) /= rhs;
}

Angle& Angle::operator/=(const Angle rhs) {
  theta_ /= rhs.theta_;
  return *this;
}

}  // namespace ogle
