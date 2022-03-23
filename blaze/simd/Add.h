#pragma once

#include <blaze/simd/BasicTypes.h>

namespace blaze {

template <typename T>
BLAZE_ALWAYS_INLINE const T operator+(const SIMDi32<T>& a, const SIMDi32<T>& b) noexcept {
  return _mm256_add_epi32((*a).value, (*b).value);
}

template <typename T1, typename T2>
BLAZE_ALWAYS_INLINE const SIMDfloat operator+(const SIMDf32<T1>& a, const SIMDf32<T2>& b) noexcept {
  return _mm256_add_ps((*a).eval().value, (*b).eval().value);
}

}  // namespace blaze