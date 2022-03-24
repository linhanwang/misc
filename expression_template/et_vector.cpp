#include <array>
#include <boost/core/demangle.hpp>
#include <initializer_list>
#include <iostream>

template <typename T, std::size_t N>
class Vector {
 public:
  using DataType = T;
  static constexpr std::size_t Size = N;

  Vector(std::initializer_list<T> list) : data_() {
    if (list.size() > N) {
      throw std::invalid_argument("Invalid setup of vector");
    }

    std::size_t i{0};
    for (const auto& item : list) data_[i++] = item;
  }

  const T& operator[](std::size_t index) const { return data_[index]; }
  T& operator[](std::size_t index) { return data_[index]; }

  template <class Expr>
  Vector<T, N>& operator=(const Expr& expr) {
    static_assert(expr.size() == N);
    for (std::size_t i = 0; i < N; ++i) data_[i] = expr[i];
    return *this;
  }

  [[nodiscard]] constexpr std::size_t size() const { return N; }

 private:
  std::array<T, N> data_{};
};

template <typename LExpr, typename RExpr>
class Sum {
 public:
  static_assert(std::is_same_v<typename LExpr::DataType, typename RExpr::DataType>);
  using DataType = typename LExpr::DataType;
  static constexpr std::size_t Size = LExpr::Size;

  explicit Sum(const LExpr& a, const RExpr& b) : a_(a), b_(b) {}

  typename LExpr::DataType operator[](std::size_t index) const { return a_[index] + b_[index]; }

  [[nodiscard]] constexpr std::size_t size() const { return Size; }

 private:
  const LExpr& a_;
  const RExpr& b_;
};

template <typename L, typename R>
Sum<L, R> operator+(const L& a, const R& b) {
  return Sum<L, R>(a, b);
}

int main() {
  Vector<int, 4> c0{1, 2, 3, 4};
  Vector<int, 4> c1{1, 2, 3, 4};
  Vector<int, 4> c2{1, 2, 3, 4};
  Vector<int, 4> c3{1, 2, 3, 4};
  Vector<int, 4> c4{1, 2, 3, 4};

  auto c = c0 + c1 + c2 + c3 + c4;

  for (int i = 0; i < c.size(); ++i) std::cout << c[i] << std::endl;

  static_assert(c.size() == 4);

  std::cout << boost::core::demangle(typeid(c).name()) << std::endl;

  return 0;
}