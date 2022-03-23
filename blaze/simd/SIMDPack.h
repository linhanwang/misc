#pragma once

#include <blaze/Inline.h>

namespace blaze {

template <typename T>
class SIMDPack {
 public:
  BLAZE_ALWAYS_INLINE constexpr T& operator*() noexcept;
  BLAZE_ALWAYS_INLINE constexpr const T& operator*() const noexcept;

 protected:
  SIMDPack() = default;
  SIMDPack(const SIMDPack&) = default;
  SIMDPack(SIMDPack&&) = default;
  ~SIMDPack() = default;
  SIMDPack& operator=(const SIMDPack&) = default;
  SIMDPack& operator=(SIMDPack&&) = default;
};

template <typename T>
BLAZE_ALWAYS_INLINE constexpr T& SIMDPack<T>::operator*() noexcept {
  return static_cast<T&>(*this);
}

template <typename T>
BLAZE_ALWAYS_INLINE constexpr const T& SIMDPack<T>::operator*() const noexcept {
  return static_cast<const T&>(*this);
}

}  // namespace blaze