#include <blaze/simd/BasicTypes.h>

#include <iostream>

int main() {
  blaze::SIMDint32 haha{_mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7)};

  blaze::SIMDint32 hehe{haha};

  hehe = blaze::SIMDint32(_mm256_set1_epi32(5));

  std::cout << haha[2] << " " << hehe[2] << std::endl;

  return 0;
}