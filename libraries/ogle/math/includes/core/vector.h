/**
 * @file Defines Vector class.
 */

#ifndef OGLE_MATH_CORE_VECTOR_H
#define OGLE_MATH_CORE_VECTOR_H

#include <assert.h>

#include <type_traits>

namespace ogle {

namespace math {

/**
* @brief Geometric vectors and points.
*/
template <typename T, int K>
class Vector {
 public:
  static_assert(K > 0, "Vectors must be of length > 0.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Vectors must use numeric types.");

  /// Type for indexing into Vector.
  using VectorIndex = std::size_t;

  /**
   * @brief Default constructor.
   * Does nothing, to reduce overhead.
   */
  Vector() noexcept {}

  /**
   * @brief Constructor.
   * @param ts Initializer list, or variable-length list of
   *   parameters, to set data. The exact number of arguments
   *   to set the Vector is required.
   */
  template <typename... U>
  Vector(U... ts)
      : data_{ts...} {
    static_assert(sizeof...(U) == K, "Wrong number of arguments.");
  }

  ///@{
  /**
   * @brief Constructor that initializes Vector from array.
   * @param data Array of values copied into vector.
   */
  Vector(const T data[K]) { memcpy(data_, data, sizeof(data_)); }
  Vector(T data[K]) { memcpy(data_, data, sizeof(data_)); }
  ///@}

  /**
  * @brief Array subscript operator that allows modification.
  * @param index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Reference to element in Vector.
  */
  T& operator[](VectorIndex index) {
    // TODO(damlaren): check with glog.
    assert(index < K);
    return data_[index];
  }

  /**
  * @brief Array subscript operator that bars modification.
  * @param index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Copy of element.
  */
  const T operator[](VectorIndex index) const {
    // TODO(damlaren): check with glog.
    assert(index < K);
    return data_[index];
  }

  /**
  * @brief Zero out the vector.
  */
  void Clear() noexcept { memset(data_, 0, sizeof(data_)); }

  ///@{
  /**
  * @brief Convenience function to access an element.
  * @return Reference to corresponding element of vector.
  */
  template <bool K2 = K >= 1 && K <= 4>
  std::enable_if_t<K2, T&> x() {
    // For some reason, this only compiles when a dependency
    // on a template variable is introduced:
    // http://cboard.cprogramming.com/cplusplus-programming/164150-sfinae-trouble.html
    return data_[0];
  }
  template <bool K2 = K >= 2 && K <= 4>
  std::enable_if_t<K2, T&> y() {
    return data_[1];
  }
  template <bool K2 = K >= 3 && K <= 4>
  std::enable_if_t<K2, T&> z() {
    return data_[2];
  }
  template <bool K2 = K == 4>
  std::enable_if_t<K2, T&> w() {
    return data_[3];
  }
  ///@}

 private:
  T data_[K];
};

}  // namespace

}  // namespace

#endif  // OGLE_MATH_CORE_VECTOR_H
