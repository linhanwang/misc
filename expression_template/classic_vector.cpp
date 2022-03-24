#include <array>
#include <initializer_list>
#include <iostream>

template <typename T, std::size_t N>
class Vector {
 public:
  Vector(std::initializer_list<T> list) : data_{} {
    if (list.size() > N) {
      throw std::invalid_argument("Invalid setup of vector");
    }

    std::size_t i{0};
    for (const auto& item : list) data_[i++] = item;
  }

  const T& operator[](std::size_t index) const { return data_[index]; }

  T& operator[](std::size_t index) { return data_[index]; }

  [[nodiscard]] constexpr std::size_t size() const { return N; }

  Vector operator+(const Vector<T, N>& other) {
    Vector<T, N> tmp{};
    for (std::size_t i = 0; i < N; ++i) tmp[i] = data_[i] + other[i];
    return tmp;
  }

 private:
  std::array<T, N> data_;
};

int main() {
  Vector<int, 4> c0{1, 2, 3, 4};
  Vector<int, 4> c1{1, 2, 3, 4};
  Vector<int, 4> c2{1, 2, 3, 4};
  Vector<int, 4> c3{1, 2, 3, 4};
  Vector<int, 4> c4{1, 2, 3, 4};

  auto c = c0 + c1 + c2 + c3 + c4;

  for (int i = 0; i < c.size(); ++i) std::cout << c[i] << std::endl;

  static_assert(c.size() == 4);

  return 0;
}