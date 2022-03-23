#pragma once

#include <blaze/simd/SIMDPack.h>
#include <immintrin.h>

#include <cstdint>

namespace blaze {

template <typename T>
struct SIMDi32 : public SIMDPack<T> {};

struct SIMDint32 : public SIMDi32<SIMDint32> {
  using This = SIMDint32;
  using BaseType = SIMDi32<This>;
  using ValueType = std::int32_t;
  using IntrinsicType = __m256i;

  BLAZE_ALWAYS_INLINE SIMDint32() noexcept : value(_mm256_setzero_si256()) {}
  BLAZE_ALWAYS_INLINE ValueType operator[](size_t i) const noexcept {
    return reinterpret_cast<const ValueType*>(&value)[i];
  }
  static constexpr std::size_t size = 8UL;

  BLAZE_ALWAYS_INLINE SIMDint32(IntrinsicType v) noexcept : value(v) {}

  template <typename T>
  BLAZE_ALWAYS_INLINE SIMDint32(const SIMDi32<T>& v) noexcept : value((*v).value) {}

  template <typename T>
  BLAZE_ALWAYS_INLINE SIMDint32& operator=(const SIMDi32<T>& v) noexcept {
    value = (*v).value;
    return *this;
  }

  IntrinsicType value;
};

template <typename T>
struct SIMDf32 : public SIMDPack<T> {};

struct SIMDfloat : public SIMDf32<SIMDfloat> {
  using This = SIMDfloat;
  using BaseType = SIMDf32<This>;
  using ValueType = float;

  using IntrinsicType = __m256;
  BLAZE_ALWAYS_INLINE SIMDfloat() noexcept : value(_mm256_setzero_ps()) {}
  BLAZE_ALWAYS_INLINE ValueType operator[](size_t i) const noexcept {
    return reinterpret_cast<const ValueType*>(&value)[i];
  }
  static constexpr std::size_t size = 8UL;

  BLAZE_ALWAYS_INLINE SIMDfloat(IntrinsicType v) noexcept : value(v) {}

  template <typename T>
  BLAZE_ALWAYS_INLINE SIMDfloat(const SIMDf32<T>& v) noexcept : value((*v).eval().value) {}

  template <typename T>
  BLAZE_ALWAYS_INLINE SIMDfloat& operator=(const SIMDf32<T>& v) noexcept {
    value = (*v).eval().value;
    return *this;
  }

  BLAZE_ALWAYS_INLINE const This& eval() const { return *this; }

  IntrinsicType value;
};

}  // namespace blaze