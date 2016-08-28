/**
 * @file angle.cc
 * @brief Implementation of angle.h.
 */

#include "math/angle.h"
#include <cmath>

namespace ogle {

Angle::Angle(const float radians)
  : theta_{Clip(radians)} {
}

std::ostream& operator<<(std::ostream& os, const Angle rhs) {
  os << rhs.degrees() << "d";
  return os;
}

const Angle operator+(const Angle lhs, const Angle rhs) {
  return Angle(lhs) += rhs;
}

Angle& Angle::operator+=(const Angle rhs) {
  theta_ = Clip(theta_ + rhs.theta_);
  return *this;
}

const Angle operator-(const Angle rhs) {
  return Angle(-rhs.radians());
}

const Angle operator-(const Angle lhs, const Angle rhs) {
  return Angle(lhs) -= rhs;
}

Angle& Angle::operator-=(const Angle rhs) {
  theta_ = Clip(theta_ - rhs.theta_);
  return *this;
}

const Angle operator*(const float scale, const Angle rhs) {
  return Angle(rhs) *= scale;
}

const Angle operator*(const Angle lhs, const float scale) {
  return Angle(lhs) *= scale;
}

Angle& Angle::operator*=(const float scale) {
  theta_ = Clip(theta_ * scale);
  return *this;
}

const Angle operator/(const Angle lhs, const float scale) {
  return Angle(lhs) /= scale;
}

Angle& Angle::operator/=(const float scale) {
  theta_ = Clip(theta_ / scale);
  return *this;
}

const bool operator<(const Angle lhs, const Angle rhs) {
  return lhs.theta_ < rhs.theta_;
}

const bool operator<=(const Angle lhs, const Angle rhs) {
  return lhs.theta_ <= rhs.theta_;
}

const bool operator>(const Angle lhs, const Angle rhs) {
  return !(lhs <= rhs);
}

const bool operator>=(const Angle lhs, const Angle rhs) {
  return !(lhs < rhs);
}

const bool operator==(const Angle lhs, const Angle rhs) {
  return lhs.theta_ == rhs.theta_;
}

const Angle Angle::FromDegrees(const float degrees) {
  return Angle(degrees * kPi / 180.f);
}

const float Angle::radians() const {
  return theta_;
}

const float Angle::degrees() const {
  return theta_ * 180.f / kPi;
}
const float Angle::Clip(const float radians) {
  return std::fmod(radians, kPi * 2.f);
}

}  // namespace ogle
